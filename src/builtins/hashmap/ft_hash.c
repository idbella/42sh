/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:23:39 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/03 22:10:07 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_get_flags(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && cmd[i][1])
		{
			if (ft_strequ(cmd[i] + 1, "r"))
			{
				ft_empty(COMMANDS);
				return (-2);
			}
			else
			{
				ft_printf_fd(2, "42sh: hash: -%c: invalid option\n", cmd[i][1]);
				return (-1);
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int		ft_hash(char **args)
{
	int		i;
	char	*file;
	int		rval;

	rval = 0;
	if (!args[0])
	{
		ft_print_hash_list();
		return (1);
	}
	if ((i = ft_get_flags(args)) < 0)
	{
		if (i == -1)
			ft_printf_fd(2, "42sh: usage: hash [-r] name [name ...]\n");
		return (1);
	}
	while (args[i])
	{
		if ((file = getfullpath(args[i])))
			ft_addtohashmap(args[i], file, COMMANDS);
		else if ((rval = 1))
			ft_printf_fd(2, "42sh: hash: %s: not found\n", args[i]);
		i++;
	}
	return (rval);
}
