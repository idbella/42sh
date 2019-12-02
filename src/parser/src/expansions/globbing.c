// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   globbing.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/09/22 15:39:47 by yoyassin          #+#    #+#             */
// /*   Updated: 2019/11/12 15:45:11 by yoyassin         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "shell.h"

// char			*get_pattern(char *line, int *i, int *pos, int *start)
// {
// 	char	*gl_pattern;
// 	char	changed;

// 	*pos = *i;
// 	changed = 0;
// 	while (*i > 0 && line[*i] != BLANK && IS_OPERATOR(*i, _AND, _NEQ))
// 	{
// 		changed = 1;
// 		(*i)--;
// 	}
// 	*start = changed ? (*i) + 1 : *i;
// 	*i = *pos;
// 	while (*i > 0 && line[*i]
// 	&& line[*i] != BLANK && IS_OPERATOR(*i, _AND, _NEQ))
// 		(*i)++;
// 	gl_pattern = ft_strsub(line, *start, (*i - *start) > 0 ? (*i - *start) : 1);
// 	*pos = ft_strpos(line, gl_pattern);
// 	return (gl_pattern);
// }

// void			fill_with_blanks(char *buf, int start, int buff_len)
// {
// 	while (buf[++start] && start <= buff_len)
// 		if (buf[start] == ' ')
// 			buf[start] = BLANK;
// }

// int				expand_wildcard(char **line, char *gl_pattern, int start, int i)
// {
// 	char	*buf;
// 	char	*s1;
// 	char	*s2;
// 	int		buff_len;
// 	int		j;

// 	buf = NULL;
// 	j = -1;
// 	if (!get_glob_buffer(gl_pattern, &buf))
// 	{
// 		free(gl_pattern);
// 		return (0);
// 	}
// 	buff_len = ft_strlen(buf);
// 	fill_with_blanks(buf, j, buff_len);
// 	s1 = ft_strsub((*line), 0, start);
// 	s2 = !(*line)[i] ? ft_strnew(0) : ft_strsub((*line), i,
// 	ft_strlen(*line) - (ft_strlen(s1) + ft_strlen(gl_pattern)));
// 	free(*line);
// 	(*line) = ft_fstrjoin(s1, buf);
// 	(*line) = ft_fstrjoin((*line), s2);
// 	free(gl_pattern);
// 	return (buff_len);
// }

// int				update_line(char **line, int *i)
// {
// 	int	buff_len;
// 	int	start;
// 	int	pos;

// 	buff_len = 0;
// 	start = 0;
// 	pos = 0;
// 	if (!(buff_len = expand_wildcard(line,
// 	get_pattern(*line, i, &pos, &start), start, *i)))
// 	{
// 		(*i)--;
// 		return (0);
// 	}
// 	*i = pos + buff_len - 1;
// 	return (1);
// }

// void			check_wildcard_c(char **line)
// {
// 	int		i;
// 	char	q;
// 	char	dq;

// 	q = 0;
// 	dq = 0;
// 	i = -1;
// 	while ((*line)[++i])
// 	{
// 		if (!q && (*line)[i] == '"' &&
// 		(*line)[i - 1 > 0 ? i - 1 : 0] != UQ_ESCAPE &&
// 		(*line)[i - 1 > 0 ? i - 1 : 0] != Q_ESCAPE)
// 			dq = !dq;
// 		else if (!dq && (*line)[i] == '\'' &&
// 		(*line)[i - 1 > 0 ? i - 1 : 0] != UQ_ESCAPE &&
// 		(*line)[i - 1 > 0 ? i - 1 : 0] != Q_ESCAPE)
// 			q = !q;
// 		if (!q && !dq && (*line)[i] == '*' &&
// 		(*line)[i - 1 > 0 ? i - 1 : 0] != UQ_ESCAPE
// 		&& (*line)[i - 1 > 0 ? i - 1 : 0] != Q_ESCAPE)
// 		{
// 			if (!update_line(line, &i))
// 				continue ;
// 		}
// 	}
// }
