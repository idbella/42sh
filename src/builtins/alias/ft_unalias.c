/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 23:45:07 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/08 11:49:29 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_unalias_all(void)
{
	ft_empty(ALIAS);
	return (0);
}

int		ft_unalias(char **cmd)
{
	char	*key;
	int		i;
	int		rval;
	char	buffer[127];

	rval = 0;
	if ((i = ft_getopt(cmd, buffer, "-a")) < 0)
	{
		ft_printf_fd(2, "42sh: unalias: -%c: invalid option\n", -i);
		ft_printf_fd(2,
			"unalias: usage: unalias [-a] name [name ...]\n");
		return (1);
	}
	if (buffer['a'])
		return (ft_unalias_all());
	while (cmd[i])
	{
		if ((key = ft_getvlaue_bykey(cmd[i], ALIAS)))
			ft_hashdelete_one(cmd[i], ALIAS);
		else if ((rval = 1))
			ft_printf_fd(2, "42sh: unalias: %s: not found\n", cmd[i]);
		i++;
	}
	return (rval);
}
