/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:49:37 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/25 11:34:52 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_freeline(t_line *alst, char **line, char c)
{
	t_line	*lst;
	int		k;
	char	*tmp;

	lst = alst;
	k = 0;
	while ((lst)->str1[k] != c && (lst)->str1[k] != '\0')
		k++;
	if (ft_strlen(lst->str1) != 0)
	{
		if ((lst)->str1[k] == '\0')
		{
			*line = ft_strdup(lst->str1);
			free(lst->str1);
			lst->str1 = ft_strnew(0);
			return (1);
		}
		tmp = lst->str1;
		*line = ft_strsub(lst->str1, 0, k);
		lst->str1 = ft_strdup(lst->str1 + k + 1);
		free(tmp);
		tmp = NULL;
		return (1);
	}
	return (0);
}

int					get_next_line(int fd, char c, char **line)
{
	static t_line	alst;
	char			buff[BUFF_SIZE + 1];
	int				j;
	char			*tmp;

	if (read(fd, buff, 0) < 0 || line == NULL)
		return (-1);
	if (!alst.str1)
		alst.str1 = ft_strnew(0);
	while ((j = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[j] = '\0';
		tmp = alst.str1;
		alst.str1 = ft_strjoin(alst.str1, buff);
		ft_strdel(&tmp);
		if (ft_strchr(alst.str1, c) != NULL)
			break ;
	}
	return (ft_freeline(&alst, line, c));
}
