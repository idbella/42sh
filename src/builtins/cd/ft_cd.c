/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:08:31 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/06 11:00:45 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*int		ft_go_dir(char **cmd, char *oldpwd)
{
	oldpwd = getcwd("NULL", 255);
	if (chdir(cmd[1]) == -1)
	{
		if (cmd[2] != NULL)
		{
			ft_putstr_fd("cd: string not in pwd: ", 2);
			ft_putendl_fd(cmd[1], 2);
		}
		else
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putendl_fd(cmd[1], 2);
		}
		return (0);
	}
	ft_addtohashmap("OLDPWD", oldpwd, INTERN);
	return (1);
}

void	ft_go_home(char *cwd)
{
	ft_addtohashmap("OLDPWD", getcwd("NULL", 255), INTERN);
	if (!(cwd = ft_getenv("HOME")))
		cwd = getpwuid(getuid());
	chdir(cwd);
}

int			ft_go_back(char **cmd)
{
	if (cmd[2] != NULL)
	{
		ft_putstr_fd("cd: string not in pwd: -", 2);
		return (0);
	}
	cwd = ft_strdup(oldpwd);
	ft_addtohashmap("OLDPWD", getcwd("NULL", 255), INTERN);
	chdir(cwd);
	free(cwd);
	return (1);
}

int		check_param_for_cd(char *param)
{
	int		i;

	i = 1;
	while (param[i] == 'L' || param[i] == 'P')
		i++;
	if (i)
		return (-1);
	return (0);
}*/

int		ft_cd(char **cmd)
{
	printf("%s", cmd[0]);
	return (1);
/*	char	*path;
	char	*oldpwd;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 3)
		return (-1);
	if (i == 1)
		if (!(path = ft_getenv("HOME")))
			path = getpwuid(getuid())->pw_dir;
	if (i == 2)
	{
		if (!check_param_for_cd(cmd[1]))
		{
			
		}
		path = ft_strdup(cmd[1]);
		oldpwd = getcwd("NULL", 255);			
		ft_addtohashmap("OLDPWD", oldpwd, INTERN);
	}*/
}
