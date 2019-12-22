/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:08:31 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 17:45:43 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*cdpath_concatenation(char *cdpath, char *directory)
{
	char		**cdpaths;
	char		*path;
	struct stat	buf;
	int			i;

	if (!(cdpaths = ft_strsplit(cdpath, ':')))
		return (NULL);
	i = 0;
	while (cdpaths[i])
	{
		if (cdpaths[i][ft_strlen(cdpaths[i]) - 1] != '/')
			path = ft_join("%s/%s", cdpaths[i], directory);
		else
			path = ft_join("%s%s", cdpaths[i], directory);
		if (!stat(path, &buf))
			if (S_ISDIR(buf.st_mode))
				return (path);
		ft_strdel(&path);
		i++;
	}
	return (NULL);
}

char	*ft_home(t_recipes *recipes)
{
	if (recipes->home)
		return (recipes->home);
	ft_putstr_fd("42sh: HOME not set\n", 2);
	return (NULL);
}

char	*ft_treat_two_arg(t_recipes *recipes, char **cmd)
{
	if (!(recipes->options = check_param_for_cd(cmd[0])))
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" is not an option\n", 2);
		return (NULL);
	}
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
	{
		if (recipes->oldpwd)
			return (recipes->oldpwd);
		ft_putstr_fd("42sh: OLDPWD not set\n", 2);
		return (NULL);
	}
	return (cmd[1]);
}

char	*ft_treat_single_arg(t_recipes *recipes, char **cmd)
{
	if ((recipes->options = check_param_for_cd(cmd[0])))
		return (ft_home(recipes));
	else if (cmd[0][0] == '-' && cmd[0][1] == '\0')
	{
		if (recipes->oldpwd)
			return (recipes->oldpwd);
		ft_putstr_fd("42sh: OLDPWD not set\n", 2);
		return (NULL);
	}
	return (cmd[0]);
}

int		ft_cd(char **cmd)
{
	int			i;
	t_recipes	recipes;

	recipes_preparations(&recipes);
	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
		ft_putstr_fd("42sh: too much argument\n", 2);
	else if (i == 0)
		recipes.curpath = ft_home(&recipes);
	else if (i == 1)
		recipes.curpath = ft_treat_single_arg(&recipes, cmd);
	else
		recipes.curpath = ft_treat_two_arg(&recipes, cmd);
	return (cd_wheels(&recipes));
}
