/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expan_operaters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <mmostafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:11:08 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/06 09:30:10 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*plus_func(t_param_expan_st *p_w)
{
	t_map	*map;

	if (p_w->type == 'P')
	{
		map = ft_getbykey(p_w->param, INTERN);
		if (map && map->value)
			return (ft_strdup(p_w->word));
		else if ((map && !map->value) || !map)
			return (NULL);
	}
	else
	{
		map = ft_getbykey(p_w->param, INTERN);
		if (map)
			return (ft_strdup(p_w->word));
		else
			return (NULL);
	}
	return (NULL);
}

char	*min_func(t_param_expan_st *p_w)
{
	t_map	*map;

	if (p_w->type == 'P')
	{
		map = ft_getbykey(p_w->param, INTERN);
		if (map && map->value)
			return (ft_strdup(map->value));
		if ((map && !map->value) || !map)
			return (ft_strdup(p_w->word));
	}
	else
	{
		map = ft_getbykey(p_w->param, INTERN);
		if (map)
			return (ft_strdup(p_w->word));
		else
			return (NULL);
	}
	return (NULL);
}

char	*assign_func(t_param_expan_st *p_w)
{
	t_map	*map;

	if (p_w->type == 'P')
	{
		map = ft_getbykey(p_w->param, INTERN);
		if (map && map->value)
			return (ft_strdup(map->value));
		if ((map && !map->value) || !map)
		{
			ft_addtohashmap(p_w->param, p_w->word, INTERN);
			return (ft_strdup(p_w->word));
		}
	}
	else
	{
		map = ft_getbykey(p_w->param, INTERN);
		if (map && map->value)
			return (ft_strdup(map->value));
		if ((map && !map->value))
			return (NULL);
		else
		{
			ft_addtohashmap(p_w->param, p_w->word, INTERN);
			return (ft_strdup(p_w->word));
		}
	}
	return (NULL);
}

char	*error_func(t_param_expan_st *p_w)
{
	t_map	*map;

	if (p_w->type == 'P')
	{
		map = ft_getbykey(p_w->param, INTERN);
		if (map && map->value)
			return (ft_strdup(map->value));
		if ((map && !map->value) || !map)
		{
			ft_putstr_fd(p_w->word, 2);
			return (NULL);
		}
	}
	else
	{
		map = ft_getbykey(p_w->param, INTERN);
		if (map && map->value)
			return (ft_strdup(map->value));
		if ((map && !map->value))
			return (NULL);
		else
		{
			ft_putstr_fd(p_w->word, 2);
			return (NULL);
		}
	}
	return (NULL);
}

char	*operators_manager(t_param_expan_st *param_word)
{
	if (param_word->type == 'P')
	{
		if (param_word->operation_type == '+')
			return (plus_func(param_word));
		if (param_word->operation_type == '-')
			return (min_func(param_word));
		if (param_word->operation_type == '=')
			return (assign_func(param_word));
		if (param_word->operation_type == '?')
			return (error_func(param_word));
	}
	if (param_word->type == 'A')
	{
		if (param_word->operation_type == '+')
			return (plus_func(param_word));
		if (param_word->operation_type == '-')
			return (min_func(param_word));
		if (param_word->operation_type == '=')
			return (assign_func(param_word));
		if (param_word->operation_type == '?')
			return (error_func(param_word));
	}
	if (param_word->type == 'F')
		return (rm_ffixers(param_word));
	return (ft_strdup(param_word->param));
}
