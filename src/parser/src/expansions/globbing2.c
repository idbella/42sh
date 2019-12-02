/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:18:41 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/02 10:17:24 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// int				errfunc(const char *epath, int errno)
// {
// 	(void)epath;
// 	(void)errno;
// 	return (0);
// }

// int				get_glob_buffer(char *gl_pattern, char **args)
// {
// 	glob_t	g;
// 	size_t	i;

// 	g.gl_pathc = 0;
// 	glob(gl_pattern, GLOB_ERR, errfunc, &g);
// 	if (!g.gl_pathc)
// 		return (0);
// 	i = 0;
// 	while (i < g.gl_pathc)
// 	{
// 		*args = ft_fstrjoin(!*args ? ft_strnew(0)
// 		: *args, ft_strdup(g.gl_pathv[i]));
// 		*args = ft_fstrjoin(*args, ft_strdup(" "));
// 		i++;
// 	}
// 	globfree(&g);
// 	return (1);
// }
