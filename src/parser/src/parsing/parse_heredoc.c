/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:33:24 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/23 15:25:24 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	store_heredoc(char **heredoc, char **buf)
{
	if (!*heredoc)
	{
		*heredoc = ft_strdup(*buf);
		free(*buf);
	}
	else
		*heredoc = ft_fstrjoin(ft_fstrjoin(*heredoc, ft_strdup("\n")), *buf);
}

char	*get_heredoc_string(char *eof)
{
	char	*buf;
	char	eol[2];
	t_init	*in;
	char	*heredoc;

	buf = NULL;
	eol[0] = 4;
	eol[1] = 0;
	in = get_shell_cfg(0)->init;
	in->heredoc_int = 1;
	heredoc = NULL;
	while (1)
	{
		buf = readline(in, "heredoc> ");
		ft_putchar('\n');
		if (!in->heredoc_int)
		{
			// break ;
			// dprintf(2," HERE : %d\n", in->heredoc_int);
		}
		if (!buf)
		{
			return ((char *)-1);
		}
		if (ft_strequ(buf, eof) || ft_strequ(buf, eol))
			break ;
		store_heredoc(&heredoc, &buf);
	}
	free(eof);
	free(buf);
	in->heredoc_int = 0;
	return (heredoc);
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
	quotes_delimiter(&eof);
	remove_quotes(&eof);
	remove_escapes(&eof, UQ_ESCAPE);
	remove_escapes(&eof, Q_ESCAPE);
	ft_memset(str + old_i, BLANK, *i - old_i);
	return (get_heredoc_string(eof));
}
