/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:15:50 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/01 20:20:10 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_map	*ft_new(t_map *mp)
{
	t_map	*nw;

	nw = ft_memalloc(sizeof(t_map));
	nw->key = ft_strdup(mp->key);
	nw->value = ft_strdup(mp->value);
	nw->type = INTERN;
	nw->hits = mp->hits;
	nw->exported = 1;
	return (nw);
}

void	ft_add_to_tmp_map(t_params *p, char *key, char *value)
{
	t_map	*map;
	t_list	*lst;

	lst = p->tmpenv;
	value = ft_strdup(value);
	while (lst)
	{
		map = lst->content;
		if (ft_strequ(map->key, key))
		{
			free(map->value);
			map->value = value;
			return ;
		}
		lst = lst->next;
	}
	map = ft_memalloc(sizeof(t_map));
	map->key = ft_strdup(key);
	map->value = value;
	ft_lstadd(&p->tmpenv, ft_lstnew(map, 0));
}

void	ft_cpyenv(t_params *p)
{
	int		i;
	t_list	*l;
	t_map	*mp;
	t_map	*nw;
	t_list	*new;

	new = NULL;
	i = 0;
	while (i < COUNT)
	{
		l = get_shell_cfg(0)->hashmap[i];
		while (l)
		{
			mp = l->content;
			if (mp->type == INTERN && mp->exported)
			{
				nw = ft_new(mp);
				ft_lstadd(&new, ft_lstnew(nw, 0));
			}
			l = l->next;
		}
		i++;
	}
	p->tmpenv = new;
}
