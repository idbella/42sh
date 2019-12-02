/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 13:58:00 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 12:45:57 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_function	*ft_is_builtin(char *arg)
{
	t_map	*map;
	int		i;

	i = 0;
	while (i < BUILTINS_COUNT)
	{
		map = &get_shell_cfg(0)->builtins[i];
		if (ft_strequ(map->key, arg))
			return (map->value);
		i++;
	}
	return (NULL);
}
