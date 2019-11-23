// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   quoting.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/09/12 17:04:55 by yoyassin          #+#    #+#             */
// /*   Updated: 2019/11/12 21:31:31 by yoyassin         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "shell.h"

// int	ending_dquote(char *line, int *i, int *j)
// {
// 	char	*endq;

// 	while ((endq = ft_strchr(line + *i + 1, '"')))
// 	{
// 		*j = *i;
// 		*i = ft_strlen(line) - ft_strlen(endq);
// 		while (*j < *i)
// 		{
// 			if (line[*j] == 92 && line[*j - 1] != Q_ESCAPE)
// 				line[*j] = Q_ESCAPE;
// 			(*j)++;
// 		}
// 		if (line[*i - 1] != Q_ESCAPE)
// 			return (1);
// 	}
// 	return (0);
// }

// int	get_input(char **line, char *p, char *eof)
// {
// 	char	*tmp;
// 	t_shell	*sh;

// 	tmp = NULL;
// 	sh = get_shell_cfg(NULL);
// 	*line = *line ? ft_fstrjoin(*line, ft_strdup("\n")) : ft_strnew(0);
// 	ft_putstr(p);
// 	tmp = read_line(&sh->line, p);
// 	if (!tmp || (!eof && tmp == (char *)-1))
// 		return (0);
// 	if (eof)
// 	{
// 		if (tmp == (char *)-1 || ft_strequ(tmp, eof))
// 		{
// 			if (tmp != (char *)-1)
// 				free(tmp);
// 			return (2);
// 		}
// 		search_and_expand(&tmp, '$');
// 	}
// 	if (!eof)
// 		sh->input = ft_fstrjoin(sh->input, ft_strjoin("\n", tmp));
// 	*line = ft_fstrjoin(*line, tmp);
// 	return (1);
// }

// int	ending_quote(char *line, int *i)
// {
// 	char	*endq;

// 	if ((endq = ft_strchr(line + *i + 1, '\'')))
// 	{
// 		*i = ft_strlen(line) - ft_strlen(endq);
// 		return (1);
// 	}
// 	return (0);
// }

// int	dquotes_checker(char **line, char *dq, int *i, int *j)
// {
// 	*dq = !(*dq);
// 	if (ending_dquote(*line, i, j))
// 		*dq = !(*dq);
// 	while (*dq)
// 	{
// 		if (!get_input(line, "dq> ", NULL))
// 			return (0);
// 		if (ending_dquote(*line, i, j))
// 			*dq = !(*dq);
// 	}
// 	return (1);
// }

// int	squotes_checker(char **line, char *q, int *i)
// {
// 	*q = !(*q);
// 	if (ending_quote(*line, i))
// 		*q = !(*q);
// 	while (*q)
// 	{
// 		if (!get_input(line, "q> ", NULL))
// 			return (0);
// 		if (ending_quote(*line, i))
// 			*q = !(*q);
// 	}
// 	return (1);
// }
