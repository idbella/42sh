/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hashmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:53:01 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/15 18:09:23 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_print_hash_list(void)
{
	int		i;
	t_list	*l;
	t_map	*map;
	char	first;

	i = -1;
	first = 1;
	while (++i < COUNT)
	{
		l = get_shell_cfg(0)->hashmap[i];
		while (l)
		{
			map = l->content;
			if (map->type == COMMANDS)
			{
				if (first)
				{
					first = 0;
					ft_printf("hits\t command\n");
				}
				ft_printf("%3d\t %s\n", map->hits, map->value);
			}
			l = l->next;
		}
	}
	if (first)
		ft_printf("42sh: hash table empty\n");
	return (0);
}
