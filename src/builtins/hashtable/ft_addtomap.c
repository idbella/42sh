/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addtomap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:52:00 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/17 14:03:47 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_map		*ft_addtohashmap(char *key, char *value, char type)
{
	t_map	*map;
	int		index;
	t_list	*l;

	if ((map = ft_getbykey(key, type)))
		free(map->value);
	else
	{
		map = malloc(sizeof(t_map));
		map->key = ft_strdup(key);
		index = ft_hash_calc(key);
		map->exported = 0;
		l = ft_lstnew(map, 0);
		ft_lstadd(&get_shell_cfg(0)->hashmap[index], l);
	}
	map->type = type;
	map->hits = 0;
	map->value = ft_strdup(value);
	if (ft_strequ(key, "PATH"))
		ft_empty(COMMANDS);
	return (map);
}
