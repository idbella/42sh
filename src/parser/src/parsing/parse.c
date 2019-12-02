/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:25:14 by merras            #+#    #+#             */
/*   Updated: 2019/11/28 15:36:57 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	-Check if line is properly quoted.
**	-Mark the operators '|' '||' '&&' '>' ... + spaces.
**	-Apply globbing '*' only.
**	-Syntax checking.
*/

void		print_parsing_res(t_job *head)
{
	int	p = 1;
	int	bj = 1;
	int	j = 1;

	while (head)
	{
		if (head->flag == BG)
		{
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
			printf("background job processes: %d\n", bj);
			printf("job cmd: %s\n", head->command);
			p = 1;
			while (head->processes)
			{
				printf("process: %d\n", p);
				while (*head->processes->arg)
				{
					printf("\targ: %s\n", *head->processes->arg);
					head->processes->arg++;
				}
				printf("redirections:\n");
				while (head->processes->redir)
				{
					printf("\ttype: %d\n", head->processes->redir->type);
					head->processes->redir = head->processes->redir->next;
				}
				printf("flag: %d\n", head->processes->flag);
				head->processes = head->processes->next;
				p++;
			}
			bj++;
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
		}
		else
		{
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
			printf("foreground job processes: %d\n", j);
			printf("job cmd: %s\n", head->command);
			p = 1;
			while (head->processes)
			{
				printf("process: %d\n", p);
				while (*head->processes->arg)
				{
					printf("\targ: %s\n", *head->processes->arg);
					head->processes->arg++;
				}
				printf("redirections:\n");
				while (head->processes->redir)
				{
					printf("\ttype: %d\n", head->processes->redir->type);
					printf("\tsrcfd: %d\n\tdstfd: %d\n\tfile: %s\n\t", head->processes->redir->src_fd,
					head->processes->redir->dst_fd, head->processes->redir->file);
					head->processes->redir = head->processes->redir->next;
				}
				printf("flag: %d\n", head->processes->flag);
				head->processes = head->processes->next;
				p++;
			}
			printf("flag: %d\n", head->flag);
			j++;
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
		}
		head = head->next;
	}
}

int			is_not_blank(char *line, int j, int i)
{
	char	valid;

	valid = 0;
	while (j < i)
	{
		if (ft_isprint((int)line[j]))
			valid = 1;
		j++;
	}
	return (valid);
}

t_job		*parse(char *input)
{
	char		**cmd_chain;
	char		*line;
	t_job		*head;

	head = NULL;
	line = ft_strdup(input);
	// if (!(line = pre_parse(ft_strdup(input))))
	// 	return (NULL);
	mark_operators(line);
	mark_bg_op(line);
	if (check_syntax_errors(line))
	{
		free(line);
		return (NULL);
	}
	// check_wildcard_c(&line);
	cmd_chain = ft_strsplit(line, SEMI_COL);
	if (!(head = get_jobs(cmd_chain, get_bg_jobs(line))))
	{
		free_array(cmd_chain);
		free(line);
		return (NULL);
	}
	free_array(cmd_chain);
	free(line);
	// t_job *tmp = head;
	// print_parsing_res(tmp);
	return (head);
}
