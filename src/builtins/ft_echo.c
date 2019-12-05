/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 22:53:34 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/03 21:57:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_echo(char **args)
{
	int		i;
	char	endl;

	endl = 1;
	i = 0;
	if (ft_strequ(args[0], "-n"))
	{
		endl = 0;
		i++;
	}
	while (args[i])
	{
		if (args[i + 1])
			ft_printf("%s ", args[i]);
		else
			ft_printf("%s", args[i]);
		i++;
	}
	if (endl)
		ft_putchar('\n');
	return (0);
}
