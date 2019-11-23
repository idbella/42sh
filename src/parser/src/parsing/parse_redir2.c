/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 00:55:29 by yoyassin          #+#    #+#             */
/*   Updated: 2019/11/23 14:04:48 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_src_fd(t_redir *curr, char *str, int *i, int *j)
{
	if (!*i || str[*i - 1] == BLANK ||
	(ft_isprint(str[*i - 1]) && !ft_isdigit(str[*i - 1])))
		curr->src_fd = str[*i] == IN_RED_OP ? 0 : 1;
	else
	{
		(*i) -= 1;
		while (*i >= 0 && str[*i] && ft_isdigit(str[*i]))
			(*i)--;
		curr->src_fd = ft_atoi(str + *i + 1);
		*j = (*i > 0) ? *i : 0;
	}
}

int		get_redir_fds(t_redir *curr, char *str, int *i)
{
	int	old_i;
	int	j;

	old_i = *i;
	j = *i;
	get_src_fd(curr, str, i, &j);
	*i = (curr->type == FD_AGGR || curr->type == CLOSE_FD) ? old_i + 2 : old_i;
	if (curr->type == FD_AGGR && ft_isdigit(str[*i]))
	{
		while (str[*i] && ft_isdigit(str[*i]))
			(*i)++;
		curr->dst_fd = ft_atoi(str + old_i + 2);
	}
	(*i) = curr->type == FD_AGGR ? (*i) - 1 : *i;
	ft_memset((void *)str + j, BLANK,
	(curr->type == CLOSE_FD || curr->type == FD_AGGR) ? *i - j + 1 : *i - j);
	return ((curr->type == FD_AGGR || curr->type == CLOSE_FD) ? 0 : 1);
}

int		get_filename_len(char *str, int *i, int *old_i)
{
	int	length;

	length = 0;
	while (str[*i] == BLANK)
	{
		(*old_i)++;
		(*i)++;
	}
	while (ft_isprint(str[*i]) || str[*i] == UQ_ESCAPE || str[*i] == Q_ESCAPE)
	{
		length++;
		(*i)++;
	}
	(*i)--;
	return (length);
}

void	get_redir_file(t_redir *curr, char *str, int *i)
{
	int	length;
	int	old_i;

	length = 0;
	str[*i] = BLANK;
	if (curr->type == O_APPEND)
	{
		str[*i + 1] = BLANK;
		(*i)++;
	}
	old_i = *i;
	length = get_filename_len(str, i, &old_i);
	if (length)
	{
		curr->file = ft_strsub(str, old_i, length);
		// apply_expansions(&curr->file);
	}
	ft_memset(str + old_i, BLANK, length);
}
