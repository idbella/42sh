/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:33:24 by yoyassin          #+#    #+#             */
/*   Updated: 2019/11/23 14:05:35 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_heredoc_string(char *eof)
{
	char	*buf;
	// int		ret;

	buf = NULL;
	while (1)
	{
		// if (!(ret = get_input(&buf, "heredoc> ", eof)))
		// {
		// 	free(eof);
		// 	return ((char *)-1);
		// }
		// else if (ret == 2)
		break ;
	}
	free(eof);
	return (buf);
}

int		get_heredoc_fd(char *str, int *i)
{
	(*i) -= 1;
	while (str[*i] && ft_isdigit(str[*i]))
		(*i)--;
	(*i) += 1;
	return (ft_atoi(str + (*i)));
}

char	*get_heredoc(char *str, int *i, int *hd_fd)
{
	char	*eof;
	int		old_i;

	old_i = *i;
	*hd_fd = (!(*i) || str[*i - 1] == BLANK || ft_isalpha(str[*i - 1])) ?
	0 : get_heredoc_fd(str, i);
	ft_memset(str + *i, BLANK, old_i - (*i) + 2);
	*i = old_i + 2;
	old_i = *i;
	while (str[*i] == BLANK)
	{
		old_i++;
		(*i)++;
	}
	while (ft_isprint(str[*i]) || str[*i] == UQ_ESCAPE || str[*i] == Q_ESCAPE)
		(*i)++;
	eof = ft_strsub(str, old_i, *i - old_i);
	// quotes_delimiter(&eof);
	// remove_quotes(&eof);
	// remove_escapes(&eof, UQ_ESCAPE);
	// remove_escapes(&eof, Q_ESCAPE);
	ft_memset(str + old_i, BLANK, *i - old_i);
	return (get_heredoc_string(eof));
}
