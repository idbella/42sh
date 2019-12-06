/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 20:43:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/06 11:33:10 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_printenv(void)
{
	char	**env;

	env = ft_serialize_env(EXPORTED_ONLY);
	while (*env)
	{
		ft_printf("export %s\n", *env);
		env++;
	}
	return (0);
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

static int	ft__export__(int export, char *arg)
{
	t_map	*map;
	char	*key;
	char	*value;

	ft_get_kv(arg, &key, &value);
	if (ft_isdigit(key[0]) && key[1] && ft_isalphanum(key + 1))
	{
		ft_printf("42sh: export: `%s': not a valid identifier\n", key);
		return (1);
	}
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
				return (0);
		}
		ft_addtohashmap(key, value, INTERN)->exported = 1;
	}
	return (0);
}

int		ft_export(char **args)
{
	int		i;
	char	export;
	int		rvalue;

	if (!args || !args[0])
		return (ft_printenv());
	if ((i = ft_get_flags(args)) < 0)
	{
		if (i == -1)
			ft_printf_fd(2,
				"42sh: usage: export [-p] [name[=value] ...]\n");
		return (1);
	}
	rvalue = 0;
	while (args[i])
	{
		export = ft_strchr(args[i], '=') ? 1 : 0;
		if (ft__export__(export, args[i]))
			rvalue = 1;
		i++;
	}
	return (rvalue);
}
