/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:19:10 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/06 14:40:04 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_addbuiltin(char *name, void *ptr)
{
	int		i;
	t_map	*blt;

	blt = get_shell_cfg(0)->builtins;
	i = 0;
	while (i < BUILTINS_COUNT)
	{
		if (!blt[i].key)
		{
			blt[i].key = name;
			blt[i].value = ptr;
			break ;
		}
		i++;
	}
}

void	ft_addtestbuiltin(char *name, void *ptr)
{
	int		i;
	t_map	*blt;

	blt = ft_getset(0)->testfunctions;
	i = 0;
	while (i < TESTFUNCTIONS_COUNT)
	{
		if (!blt[i].key)
		{
			blt[i].key = name;
			blt[i].value = ptr;
			break ;
		}
		i++;
	}
}

void	ft_addblt()
{
	ft_addbuiltin("echo", ft_echo);
	ft_addbuiltin("cd", ft_cd);
	ft_addbuiltin("export", ft_export);
	ft_addbuiltin("set", ft_set);
	ft_addbuiltin("hash", ft_hash);
	ft_addbuiltin("jobs", ft_jobs);
	ft_addbuiltin("fg", ft_fg);
	ft_addbuiltin("bg", ft_bg);
	ft_addbuiltin("unset", ft_unset);
	ft_addbuiltin("exit", ft_exit);
	ft_addbuiltin("type", ft_type);
	ft_addbuiltin("alias", ft_alias);
	ft_addbuiltin("unalias", ft_unalias);
	ft_addbuiltin("test", ft_test);
	ft_addbuiltin("fc", ft_fc);
}

void	ft_fill(t_shell *shell)
{
	int i;

	i = 0;
	while (i < BUILTINS_COUNT)
		shell->builtins[i++].key = NULL;
	i = 0;
	while (i < TESTFUNCTIONS_COUNT)
		ft_getset(0)->testfunctions[i++].key = NULL;
	ft_addblt();
}

void	ft_init_builtins(char **env)
{
	char	*key;
	char	*value;
	t_shell	*shell;
	t_map	*mp;

	ft_init_hash();
	while (*env)
	{
		
		ft_get_kv(*env, &key, &value);
		mp = ft_addtohashmap(key, value, INTERN);
		free(key);
		free(value);
		mp->exported = 1;
		env++;
	}
	shell = get_shell_cfg(0);
	ft_fill(shell);
	ft_getset(0)->test_operators = ft_strsplit("\127,-b,-c,-d,-e,-f,-L,-p,-S,\
-u,-g,-r,-w,-x,-z,-s,=,!=,-eq,-ne,-ge,-lt,-le,-gt", ',');
}
