/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:08:31 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/14 11:05:44 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

typedef struct s_recipes
{
	char		*oldpwd;
	char		*pwd;
	char		*home;
	char		*cdpath;
	char		*curpath;
	char		options;
	int			mute;
	struct stat	buf;
}				t_recipes;

int		errors_container(int err, t_recipes *recipes)
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
		ft_putstr_fd("not a directory\n", 2);
	}
	if (err == 4)
	{
		ft_putstr_fd("42sh :", 2);
		ft_putstr_fd(" No such file or directory: ", 2);
		ft_putendl_fd(recipes->curpath, 2);
	}
	return (-1);
}

int		chdir_operations(t_recipes *recipes)
{
	if (stat(recipes->curpath, &recipes->buf) != -1)
	{
		if (S_ISDIR(recipes->buf.st_mode))
		{
			if (!access(recipes->curpath, X_OK))
			{	
				ft_addtohashmap("OLDPWD", getcwd(NULL, 4097), INTERN);
				if (chdir(recipes->curpath) != -1)
				{
					if (recipes->mute == 1)
						ft_putendl(recipes->curpath);
					lstat(recipes->curpath, &recipes->buf);
					if (recipes->options == 'P' && S_ISLNK(recipes->buf.st_mode))
						ft_addtohashmap("PWD", getcwd(NULL, 4097), INTERN);
					else
						ft_addtohashmap("PWD", getcwd(NULL, 4097), INTERN);
				}
				else
					return (errors_container(1, recipes));
			}
			else
				return (errors_container(2,recipes));
		}
		else
			return (errors_container(3, recipes));
	}
	else
		return (-1);
	return (0);
}

char	check_param_for_cd(char *param)
{
	int		i;

	i = 0;
	if (param[i] == '-')
		i++;
	while (param[i] == 'L' || param[i] == 'P')
		i++;
	if (param[i - 1] != 'P' && param[i - 1] != 'L')
		return (0);
	return (param[i - 1]);
}

char	*get_dir(char *operand, t_recipes *recipes)
{
	if (!ft_strcmp("-", operand))
	{
		if (!recipes->oldpwd)
			ft_putstr_fd("42sh: OLDPWD not set\n", 2);
		else
			return (recipes->oldpwd);
	}
	else
		return (ft_strdup(operand));
	return (NULL);
}

char	*cdpath_concatenation(char *cdpath, char *directory)
{
	char		**cdpaths;
	char		*path;
	struct stat	buf;
	int			i;

	if (!(cdpaths = ft_strsplit(cdpath,':')))
		return (NULL);
	i = 0;
	while (cdpaths[i])
	{
		if (cdpaths[i][ft_strlen(cdpaths[i]) - 1] != '/')
			path = ft_join("%s/%s", cdpaths[i], directory);
		else
			path = ft_strjoin(cdpaths[i], directory);
		if (!stat(path, &buf))
			if (S_ISDIR(buf.st_mode))
				return (path);
		ft_strdel(&path);
		i++;
	}
	return (NULL);
}

void	recipes_preparations(t_recipes *recipes)
{
	recipes->oldpwd = ft_getenv("OLDPWD");
	recipes->pwd = ft_getenv("PWD");
	recipes->home = ft_getenv("HOME");
	recipes->cdpath = ft_getvlaue_bykey("CDPATH", INTERN);
	recipes->curpath = NULL;
	recipes->options = 0;
	recipes->mute = 0;
}

int		ft_cd(char **cmd)
{
	int			i;
	char		*tmp;
	t_recipes	recipes;

	recipes_preparations(&recipes);
	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
		ft_putstr_fd("42sh: too much argument\n", 2);
	else if (i == 0)
	{
		if (!recipes.home)
			ft_putstr_fd("42sh: HOME not set\n", 2);
		else
			recipes.curpath = recipes.home;
	}
	else if (i == 1)
	{
		if ((recipes.options = check_param_for_cd(cmd[0])))
		{
			if (!recipes.home)
				ft_putstr_fd("42sh: HOME not set\n", 2);
			else
				recipes.curpath = recipes.home;	
		}
		else if (cmd[0][0] == '-' && cmd[0][1] == '\0')
		{
			if (!recipes.oldpwd)
				ft_putstr_fd("42sh: HOME not set\n", 2);
			else
				recipes.curpath = recipes.oldpwd;		
		}
		else
			recipes.curpath = get_dir(cmd[0], &recipes);
	}
	else
	{
		if (!(recipes.options = check_param_for_cd(cmd[0])))
		{
			ft_putstr_fd("42sh: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd("is not an option\n", 2);
		}
		else
			recipes.curpath = get_dir(cmd[1], &recipes);	
	}
	printf("CURPATH == %s, OPTION == %d\n", recipes.curpath, recipes.options);
	if (recipes.curpath)
	{
		if (chdir_operations(&recipes) == -1)
		{
			tmp = recipes.curpath;
			recipes.curpath = cdpath_concatenation(recipes.cdpath,recipes.curpath);
			if (recipes.curpath)
			{
				recipes.mute = 1;
				chdir_operations(&recipes);
			}
			else if ((recipes.curpath = tmp))
				return (errors_container(4, &recipes));
		}
	}
	return (1);
}
