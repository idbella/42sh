/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 10:31:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/08 13:25:14 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_getopt(char **args, char *buffer, char *valid)
{
	int		i0;
	int		i1;
	int		found;
	int		option;

	found = 0;
	i0 = -1;
	ft_bzero(buffer, 127);
	while (args[++i0])
	{
		if (ft_strequ(args[i0], "--"))
			return (i0 + 1);
		if (args[i0][0] == '-')
		{
			i1 = 0;
			while (args[i0][++i1])
			{
				;
				if (!ft_strchr(valid, args[i0][i1]))
					return (-args[i0][i1]);
				if ((option = (int)args[i0][i1]) > 0)
					buffer[option] = 1;
				found = 1;
			}
		}
		else
			return (i0);
	}
	return (i0);
}
