/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 14:51:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/29 19:37:17 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*getfullpath(char *name)
{
	char	*path;
	char	**entrys;
	int		i;
	char	*fullname;

	fullname = NULL;
	if (ft_strchr(name, '/'))
		return (ft_strdup(name));
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
				free(fullname);
				i++;
			}
			ft_free_array(entrys);
		}
	}
	return (fullname);
}

char	*ft_findfile(char *name, char **error)
{
	char	*file;
	t_stat	state;

	file = NULL;
	if ((file = ft_getvlaue_bykey(name, COMMANDS)))
	{
		if (access(file, F_OK))
			file = NULL;
		else
			file = ft_strdup(file);
	}
	if (!file && ((file = getfullpath(name))))
		ft_addtohashmap(name, file, COMMANDS)->hits = 1;
	if (file && !stat(file, &state))
	{
		if (S_ISREG(state.st_mode))
			return (file);
		else if (S_ISDIR(state.st_mode))
			*error = "42sh: %s: is a directory\n";
		else
			*error = "42sh: %s: permission denied\n";
	}
	return (NULL);
}
