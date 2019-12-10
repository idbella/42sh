/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:25:14 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/10 14:37:54 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	-Check if line is properly quoted.
**	-Mark the operators '|' '||' '&&' '>' ... + spaces.
**	-Syntax checking.
**  -TO DO: - revise syntax checking + add support for ${} and $().
**			- flag quoted arg[0]
**			- add <() >()
**			- fix alias expansion.
**			- fix ${?}
**			- heredoc.
**			- search for errors.
**			- norminette and leaks.
**			- more tests.
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

int			is_word(char *word)
{
	while (*word)
	{
		if (!ft_isalnum(*word) && *word != '_' && *word != '-')
			return (0);
		word++;
	}
	return (1);
}

int			match_expr(char *token)
{
	char	err;
	int		pos;
	char	*s[2];

	err = 0;
	pos = 0;
	if (token[0] != '#')
	{

		if ((pos = ft_strpos(token, ":-")) != -1)
		{
			s[0] = ft_strsub(token, 0, pos);
			s[1] = ft_strdup(token + pos + 1);
			// printf("s1:%s\ns2:%s\n", s[0], s[1]);
		}
	}
	else
	{
		if (!is_word(token + 1))
			err = 1;
	}
	if (err)
		ft_putendl_fd("42sh: bad substitution", 2);
	free(token);
	return (err);
}

int			subst_syntax(char *line) //ONLY SIMPLE FORMAT FOR NOW
{
	(void)line;
	// printf("line: %s\n", line);
	return (0);
}

t_job		*parse(char *input)
{
	char		**cmd_chain;
	char		*line;
	t_job		*head;
	t_token		*tokens;

	head = NULL;
	if (!ft_strlen(input))
		return (NULL);
	line = ft_strdup(input);
	// if (!(line = pre_parse(ft_strdup(input))))
	// 	return (NULL);
	mark_operators(line);
	mark_bg_op(line);
	if (check_syntax_errors(line) || subst_syntax(line))
	{
		free(line);
		return (NULL);
	}
	tokens = alias_expansion(&line);
	free(line);
	line = gather_tokens(tokens);
	// printf("line: %s\n", line);
	mark_operators(line);
	mark_bg_op(line);
	// printf("line: %s\n", line);
	// printf("line: %s\n", line);
	// printf("breakdown:\n");
	// for (int i = 0; line[i]; i++)
		// printf("c: %d\n", line[i]);
	if (check_syntax_errors(line) /*|| subst_syntax(line)*/)
	{
		free(line);
		return (NULL);
	}
	cmd_chain = ft_strsplit(line, SEMI_COL);
	if (!(head = get_jobs(cmd_chain, get_bg_jobs(line))))
	{
		free_array(cmd_chain);
		free(line);
		return (NULL);
	}
	free_array(cmd_chain);
	free(line);
	return (head);
}
