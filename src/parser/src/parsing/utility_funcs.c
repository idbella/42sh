/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:50:04 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/08 21:04:56 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	append_lst(void **h, void **c, void **t, char type)
{
	if (!*h)
	{
		*h = *c;
		*t = *c;
	}
	else
	{
		if (type == 1)
			((t_job *)(*t))->next = *c;
		else
			((t_process *)(*t))->next = *c;
		*t = *c;
	}
}

int		set_flag(void *curr, int flag, char type)
{
	if (!type || type == 1)
	{
		((t_process *)curr)->flag = flag;
		((t_process *)curr)->status = 0;
		((t_process *)curr)->next = NULL;
		return (flag == PIPE ? 1 : 2);
	}
	else
	{
		((t_job *)curr)->flag = flag;
		((t_job *)curr)->next = NULL;
		return (flag == BG ? 1 : 2);
	}
}

char	*skip_operators(char type, char *token, int *start, int *j)
{
	(*start) += (*j) - (*start);
	if (type == 1)
	{
		while (token[*j] && token[*j] != AND && token[*j] != OR)
			(*j)++;
	}
	else if (type == 2)
	{
		while (token[*j] && token[*j] != BG)
			(*j)++;
	}
	else if (type == 3)
	{
		while (token[*j]
		&& token[*j] != PIPE && token[*j] != AND && token[*j] != OR)
			(*j)++;
	}
	else if (type == 4)
	{
		while (token[*j] && token[*j] != BG
		&& token[*j] != PIPE && token[*j] != AND && token[*j] != OR)
			(*j)++;
	}
	else
	{
		while (token[*j] && token[*j] != PIPE)
			(*j)++;
	}
	if (!token[(*j) - (*start)])
		return (ft_strsub(token, *start, (*j) - (*start) + 1));
	return (ft_strsub(token, *start, (*j) - (*start)));
}

char	*get_cmd_string(char *s)
{
	char	*str;
	int		i;

	str = ft_strdup(s);
	i = 0;
	while (s[i])
	{
		if (s[i] == BLANK)
			str[i] = ' ';
		else if (s[i] == PIPE || s[i] == OR)
			str[i] = '|';
		else if (s[i] == OUT_RED_OP || s[i] == APP_OUT_RED_OP)
			str[i] = '>';
		else if (s[i] == IN_RED_OP || s[i] == HEREDOC_OP)
			str[i] = '<';
		else if (s[i] == AND)
			str[i] = '&';
		else if (s[i] == Q_ESCAPE || s[i] == UQ_ESCAPE)
			str[i] = '\\';
		else if (s[i] == DOLLAR)
			s[i] = '$';
		i++;
	}
	return (str);
}

int		get_list_node(char type, void **curr, char *str)
{
	if (type)
	{
		*curr = (t_job *)malloc(sizeof(t_job));
		if (!(((t_job *)*curr)->processes = get_process_list(str, type)))
			return (0);
		((t_job *)*curr)->command = get_cmd_string(str);
		((t_job *)*curr)->flag = 0;
		((t_job *)*curr)->sub = 0;
		((t_job *)*curr)->next = NULL;
	}
	else
	{
		*curr = (t_process *)malloc(sizeof(t_process));
		((t_process *)*curr)->p0 = -1;
		((t_process *)*curr)->status = 0;
		((t_process *)*curr)->heredoc = NULL;
		((t_process *)*curr)->heredoc_fd = -1;
		if ((check_redirections(str, ((t_process *)*curr))) == (char *)-1)
			return (0);
		if (str && str != (char *)-1)
			((t_process *)*curr)->arg = ft_strsplit(str, BLANK);
		else
			str = NULL;
		apply_expansions(((t_process *)*curr)->arg);
		((t_process *)*curr)->flag = 0;
		((t_process *)*curr)->next = NULL;
	}
	return (1);
}
