/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:19:10 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 11:01:09 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_init_builtins(char **env)
{
	char	*key;
	char	*value;

	ft_init_hash();
	while (*env)
	{
		ft_get_kv(*env, &key, &value);
		ft_addtohashmap(key, value, INTERN)->exported = 1;
		env++;
	}
	get_shell_cfg(0)->env = ft_serialize_env(EXPORTED_ONLY);
}
