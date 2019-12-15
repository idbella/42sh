/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 14:51:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/15 09:25:53 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*getfullpath(char *name)
{
	char	*path;
	char	**entrys;
	int		i;
	char	*fullname;

	fullname = NULL;
	if ((path = ft_getenv("PATH")))
	{
		if ((entrys = ft_strsplit(path, ':')))
		{
			i = 0;
			while (entrys[i])
			{
				fullname = ft_join("%s/%s", entrys[i], name);
				if (!access(fullname, F_OK))
					break ;
				ft_strdel(&fullname);
				i++;
			}
			ft_free_array(entrys);
		}
	}
	return (fullname);
}

char	*ft_findfile(char *name, char **error, char add)
{
	char		*file;
	t_stat		state;
	t_params	*p;

	p = ft_getset(0)->params;
	file = NULL;
	if ((file = ft_getvlaue_bykey(name, COMMANDS)))
	{
		if (access(file, F_OK))
			file = NULL;
		else
			file = ft_strdup(file);
	}
	if (ft_strchr(name, '/'))
		file = ft_strdup(name);
	if (!file && ((file = getfullpath(name))) && add)
		ft_addtohashmap(name, file, COMMANDS)->hits = 1;
	if (file && !stat(file, &state))
	{
		if (!access(file, X_OK))
		{
			if (S_ISREG(state.st_mode))
				return (file);
			else if (S_ISDIR(state.st_mode))
			{
				*error = "42sh: %s: is a directory\n";
				return (NULL);
			}
		}
		*error = "42sh: %s: permission denied\n";
	}
	return (NULL);
}
