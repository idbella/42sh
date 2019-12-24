/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_wheels.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:59:01 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/24 19:20:16 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		cd_wheels(t_recipes *recipes)
{
	char	*tmp;

	if (recipes->curpath)
	{
		if (chdir_operations(recipes) == -1)
		{
			tmp = recipes->curpath;
			recipes->curpath = cdpath_concatenation(recipes->cdpath,
					recipes->curpath);
			recipes->mute = 1;
			if (recipes->curpath)
			{
				chdir_operations(recipes);
				ft_strdel(&tmp);
			}
		}
		ft_strdel(&(recipes->curpath));
		return (1);
	}
	ft_strdel(&(recipes->curpath));
	return (0);
}
