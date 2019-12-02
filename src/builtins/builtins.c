/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:19:10 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 09:58:52 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_fill(t_shell *shell)
{
	shell->builtins[0].key = "echo";
	shell->builtins[1].key = "cd";
	shell->builtins[2].key = "export";
	shell->builtins[2].value = ft_export;
	shell->builtins[3].key = "set";
	shell->builtins[3].value = ft_set;
	shell->builtins[4].key = "hash";
	shell->builtins[4].value = ft_hash;
	shell->builtins[5].key = "jobs";
	shell->builtins[5].value = ft_jobs;
	shell->builtins[6].key = "fg";
	shell->builtins[6].value = ft_fg;
	shell->builtins[7].key = "bg";
	shell->builtins[7].value = ft_bg;
	shell->builtins[8].key = "unset";
	shell->builtins[8].value = ft_unset;
	shell->builtins[9].key = "exit";
	shell->builtins[9].value = ft_exit;
	shell->builtins[10].key = "type";
	shell->builtins[10].value = ft_type;
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
}
