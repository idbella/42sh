/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:53:56 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/04 11:12:12 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// int			quotes_checker(char **line, char *quote, int *i, int *j)
// {
// 	if (!j)
// 	{
// 		if (!(squotes_checker(line, quote, i)))
// 		{
// 			free(*line);
// 			return (0);
// 		}
// 	}
// 	else
// 	{
// 		if (!(dquotes_checker(line, quote, i, j)))
// 		{
// 			free(*line);
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

// char		*pre_parse(char *line)
// {
// 	int		i;
// 	int		j;
// 	char	q;
// 	char	dq;

// 	q = 0;
// 	dq = 0;
// 	i = 0;
// 	while (line[i])
// 	{
// 		if (!q && line[i] == '"' && NOT_ESCAPED(i))
// 		{
// 			if (!quotes_checker(&line, &dq, &i, &j))
// 				return (NULL);
// 		}
// 		else if (!dq && line[i] == '\'' && NOT_ESCAPED(i))
// 		{
// 			if (!quotes_checker(&line, &q, &i, NULL))
// 				return (NULL);
// 		}
// 		else if (!q && !dq && line[i] == 92 && NOT_ESCAPED(i))
// 			line[i] = UQ_ESCAPE;
// 		i++;
// 	}
// 	return (line);
// }

int			get_bg_jobs(char *line)
{
	int	i;
	int	bg;

	i = 0;
	bg = 0;
	while (line[i])
	{
		if (line[i] == BG)
			bg++;
		i++;
	}
	return (bg);
}

void		mark_bg_op(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i + 1] != OUT_RED_OP &&
			line[(i - 1 > 0) ? i - 1 : 0] != OUT_RED_OP &&
			line[(i - 1 > 0) ? i - 1 : 0] != IN_RED_OP &&
			line[i] == '&')
			line[i] = BG;
	}
}
