/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 20:43:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/01 20:52:07 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_printenv(void)
{
	char	**env;

	env = ft_serialize_env(EXPORTED_ONLY);
	while (*env)
	{
		ft_printf("export %s\n", *env);
		env++;
	}
}

static int	ft_get_flags(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (*cmd[i] == '-')
		{
			if (ft_strequ(cmd[i] + 1, "p"))
			{
				ft_printenv();
				return (-2);
			}
			else
			{
				ft_printf_fd(2, "42sh: export: -%c: invalid option\n", cmd[i]);
				return (-1);
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

char	ft_isalphanum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void		ft_export(char **args)
{
	int		i;
	char	*key;
	char	*value;
	char	export;
	t_map	*map;

	if (!args || !args[0])
	{
		ft_printenv();
		return ;
	}
	if ((i = ft_get_flags(args)) < 0)
	{
		if (i == -1)
			ft_printf_fd(2,
				"42sh: usage: export [-p] [name[=value] ...]\n");
		return ;
	}
	while (args[i])
	{
		export = ft_strchr(args[i], '=') ? 1 : 0;
		ft_get_kv(args[i], &key, &value);
		if (ft_isdigit(key[0]) || !ft_isalphanum(key))
			ft_printf("42sh: export: `%s': not a valid identifier\n", key);
		else
		{
			if (!export)
			{
				if ((map = ft_getbykey(key, INTERN)))
				{
					map->exported = 1;
					value = map->value;
				}
				else
				{
					i++;
					continue ;
				}
			}
			ft_addtohashmap(key, value, INTERN)->exported = 1;
		}
		i++;
	}
}
