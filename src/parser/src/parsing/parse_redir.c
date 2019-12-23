/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 04:19:50 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/22 15:14:39 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		append_redir(t_redir **h, t_redir **c, t_redir **t)
{
	if (!*h)
	{
		*h = *c;
		*t = *c;
	}
	else
	{
		(*t)->next = *c;
		*t = *c;
	}
}

static t_redir	*get_node(void)
{
	t_redir *node;

	if (!(node = (t_redir *)malloc(sizeof(t_redir))))
		exit(2);
	node->type = -1;
	node->src_fd = -1;
	node->dst_fd = -1;
	node->file = NULL;
	node->next = NULL;
	return (node);
}

void			get_redir_type(t_redir *curr, char *str, int i)
{
	if (str[i + 1] != '&' && (str[i] == OUT_RED_OP || str[i] == IN_RED_OP))
		curr->type = (str[i] == OUT_RED_OP) ? O_WRONLY : O_RDONLY;
	else if (str[i] == APP_OUT_RED_OP)
		curr->type = O_APPEND;
	if (curr->type != O_APPEND)
	{
		if (str[i] == OUT_RED_OP && (str[(i - 1 > 0) ? i - 1 : 0] == '&' ||
		(str[i + 1] == '&' && !ft_isdigit(str[i + 2])
		&& !ft_isdigit(str[(i - 1 > 0) ? i - 1 : 0])
		&& str[i + 2] != '-')))
		{
			curr->src_fd = BOTH_FDS;
			curr->type = O_WRONLY;
			if (i > 0)
				str[i - 1] = (str[i - 1] == '&') ? BLANK : str[i - 1];
			str[i + 1] = (str[i + 1] == '&') ? BLANK : str[i + 1];
		}
	}
	if (curr->type != O_APPEND && str[i + 2] && str[i + 1] == '&')
		curr->type = (str[i + 2] == '-') ? CLOSE_FD : FD_AGGR;
}

int				get_redir_info(t_redir *curr, char *str, int *i)
{
	get_redir_type(curr, str, *i);
	if (curr->src_fd != BOTH_FDS)
	{
		if (!get_redir_fds(curr, str, i))
			return (0);
	}
	get_redir_file(curr, str, i);
	return (1);
}

char			*check_redirections(char *str, t_process *cmd)
{
	int		i;
	t_redir	*curr;
	t_redir	*head;
	t_redir	*tail;

	head = NULL;
	curr = NULL;
	tail = NULL;
	i = 0;
	while (str[i])
	{
		if (IS_REDIRECTION)
		{
			curr = get_node();
			append_redir(&head, &curr, &tail);
			if (!get_redir_info(curr, str, &i))
				continue ;
		}
		else if (str[i] == HEREDOC_OP)
			cmd->heredoc = get_heredoc(str, &i, &cmd->heredoc_fd);
		i++;
	}
	cmd->redir = head;
	return (cmd->heredoc == (char *)-1 ? (char *)-1 : str);
}
