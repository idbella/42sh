/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_and_path_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:44:09 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/22 18:16:16 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			errors_container(int err, t_recipes *recipes)
{
	if (recipes->mute == 1)
		return (-1);
	if (err == 1)
		ft_putstr_fd("42sh: chdir failed\n", 2);
	if (err == 2)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(recipes->curpath, 2);
	}
	if (err == 3)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(recipes->curpath, 2);
		ft_putstr_fd(" not a directory\n", 2);
	}
	if (err == 4)
	{
		ft_putstr_fd("42sh :", 2);
		ft_putstr_fd(" No such file or directory: ", 2);
		ft_putendl_fd(recipes->curpath, 2);
	}
	return (-1);
}

static char	*remove_dots(char **paths, t_recipes *recipes, int i)
{
	recipes->curpath = ft_strdup("/");
	i = 0;
	while (paths[i])
	{
		if (paths[i][0] != -1 && i == 0)
			recipes->curpath = ft_join("%s%s", recipes->curpath, paths[i]);
		else if (paths[i][0] != -1 && i != 0)
			recipes->curpath = ft_join("%s/%s", recipes->curpath, paths[i]);
		i++;
	}
	ft_free_array(paths);
	return (recipes->curpath);
}

static char	*operate_dots(char **paths, int i)
{
	while (paths[i])
	{
		if (!ft_strcmp("..", paths[i]) && paths[i][0] != -1)
		{
			paths[i][0] = -1;
			while (paths[i][0] == -1 && i)
				i--;
			if (i == 0)
				return (ft_strdup("/"));
			else
				paths[i][0] = -1;
		}
		if (!ft_strcmp(".", paths[i]) && paths[i][0] != -1)
			paths[i][0] = -1;
		i++;
	}
	return (NULL);
}

static char	*curpath_handling(t_recipes *recipes)
{
	int		i;
	char	**paths;

	if (recipes->curpath[0] != '/')
	{

		if (!ft_strcmp("/", getcwd(NULL, 4097)))
		{	
			recipes->curpath = ft_join("%s%s",
					getcwd(NULL, 4097), recipes->curpath);
		}
		else if (recipes->options == 'P')
		{
			recipes->curpath = ft_join("%s/%s",
					getcwd(NULL, 4097), recipes->curpath);
		}
		else
			recipes->curpath = ft_join("%s/%s",
					get_shell_cfg(0)->pwd, recipes->curpath);
	}
	paths = ft_strsplit(recipes->curpath, '/');
	i = 0;
	recipes->curpath = operate_dots(paths, i);
	if (recipes->curpath)
	{
		ft_free_array(paths);
		return (ft_strdup(recipes->curpath));
	}
	return (remove_dots(paths, recipes, i));
}

int			chdir_operations(t_recipes *recipes)
{
	if ((recipes->helper = stat(recipes->curpath, &recipes->buf)) != -1)
	{
		if (S_ISDIR(recipes->buf.st_mode))
		{
			if (!access(recipes->curpath, X_OK))
			{
				ft_addtohashmap("OLDPWD", ft_getenv("PWD"), INTERN);
				recipes->curpath = curpath_handling(recipes);
				if (chdir(recipes->curpath) != -1)
				{
					if (recipes->mute == 1)
						ft_putendl(recipes->curpath);
					ft_addtohashmap("PWD", recipes->curpath, 1)->exported = 1;
					ft_strdel(&(get_shell_cfg(0)->pwd));
					get_shell_cfg(0)->pwd = ft_strdup(recipes->curpath);
				}
				else
					return (errors_container(1, recipes));
			}
			else
				return (errors_container(2, recipes));
		}
		else
			return (errors_container(3, recipes));
	}
	return (recipes->helper);
}
