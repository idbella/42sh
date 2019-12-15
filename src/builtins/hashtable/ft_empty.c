/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:49:19 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 09:13:48 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_empty(char type)
{
	int		i;
	t_list	**l;
	t_map	*map;
	t_list	*list;
	t_list	*tmp;
	t_list	*prev;

	i = -1;
	l = get_shell_cfg(0)->hashmap;
	while (++i < COUNT)
	{
		list = l[i];
		prev = NULL;
		while (type && list)
		{
			map = list->content;
			tmp = list->next;
			if (type == ANYHASH || map->type == type)
			{
				free(map->key);
				free(map->value);
				free(map);
				free(list);
				if (prev)
					prev->next = tmp;
				else
					l[i] = tmp;
			}
			list = tmp;
		}
		if (type == 0 || type == ANYHASH)
			l[i] = NULL;
	}
}
