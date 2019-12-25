/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapdelete_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:50:06 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 11:12:05 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_free(t_map *map, t_list *lst)
{
	free(map->key);
	free(map->value);
	free(map);
	free(lst);
}

void		ft_hashdelete_one(char *key, char type)
{
	t_list	*lst;
	t_list	*prev;
	t_map	*map;
	t_list	*next;
	int		index;

	index = ft_hash_calc(key);
	lst = get_shell_cfg(0)->hashmap[index];
	prev = NULL;
	while (lst)
	{
		map = lst->content;
		if (map->type == type && ft_strequ(key, map->key))
		{
			next = lst->next;
			ft_free(map, lst);
			if (prev)
				prev->next = next;
			else
				get_shell_cfg(0)->hashmap[index] = next;
			if (ft_strequ(key, "PATH"))
				ft_empty(COMMANDS);
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
}
