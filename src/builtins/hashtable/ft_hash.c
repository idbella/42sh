/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:23:39 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/15 18:08:06 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_hash(char **args)
{
	int		i;
	char	*file;
	int		rval;
	char	options[127];

	rval = 0;
	if (!args[0])
		return (ft_print_hash_list());
	if ((i = ft_getopt(args, options, "r")) < 0)
	{
		ft_printf_fd(2, "42sh: hash: -%c: invalid option\n", -i);
		ft_printf_fd(2, "42sh: usage: hash [-r] name [name ...]\n");
		return (1);
	}
	if (options['r'])
		ft_empty(COMMANDS);
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
