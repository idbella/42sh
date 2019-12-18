/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:34:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/17 15:13:02 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*ft_getenv(char *key)
{
	t_map	*map;

	map = ft_getbykey(key, INTERN);
	return (map && map->exported ? map->value : NULL);
}

static size_t	ft_envcount(char exported)
{
	size_t	count;
	int		i;
	t_list	*lst;
	t_map	*map;

	i = 0;
	count = 0;
	while (i < COUNT)
	{
		lst = get_shell_cfg(0)->hashmap[i];
		while (lst)
		{
			map = lst->content;
			if (map->type == INTERN &&
				(exported & INCLUDE_UNEXPORTED ||
				(exported & EXPORTED_ONLY && map->exported)))
				count++;
			lst = lst->next;
		}
		i++;
	}
	return (count);
}

char			**ft_serialize_env(char exported)
{
	int		i;
	t_list	*lst;
	t_map	*map;
	char	**env;
	int		index;

	i = 0;
	env = ft_memalloc(sizeof(char *) * (ft_envcount(exported) + 1));
	index = 0;
	while (i < COUNT)
	{
		lst = get_shell_cfg(0)->hashmap[i];
		while (lst)
		{
			map = lst->content;
			if (map->type == INTERN &&
				(exported & INCLUDE_UNEXPORTED ||
				(exported & EXPORTED_ONLY && map->exported)))
			{
				if (exported & KEYS_ONLY)
					env[index++] = ft_join("%s", map->key);
				else
					env[index++] = ft_join("%s=%s", map->key, map->value);
			}
			lst = lst->next;
		}
		i++;
	}
	env[index] = NULL;
	return (env);
}
