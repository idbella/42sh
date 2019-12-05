/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 23:45:07 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/03 22:35:00 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_unalias_all(void)
{
	ft_empty(ALIAS);
}

static int	ft_get_flags(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (*cmd[i] == '-')
		{
			if (ft_strequ(cmd[i] + 1, "a"))
			{
				ft_unalias_all();
				return (-2);
			}
			else
			{
				ft_printf_fd(2, "42sh: unalias: -%c: invalid option\n", cmd[i]);
				return (-1);
			}
		}
		else
			return (i);
		i++;
	}
	return (-1);
}

int		ft_unalias(char **cmd)
{
	char	*key;
	int		i;
	int		rval;

	rval = 0;
	if ((i = ft_get_flags(cmd)) < 0)
	{
		if (i == -1)
			ft_printf_fd(2,
				"unalias: usage: unalias [-a] name [name ...]\n");
		return (1);
	}
	while (cmd[i])
	{
		if ((key = ft_getvlaue_bykey(cmd[i], ALIAS)))
			ft_hashdelete_one(cmd[i], ALIAS);
		else
		{
			rval = 1;
			ft_printf_fd(2, "42sh: unalias: %s: not found\n", cmd[i]);
		}
		i++;
	}
	return (rval);
}
