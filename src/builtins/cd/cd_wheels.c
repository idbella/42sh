/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_wheels.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:59:01 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/23 20:29:17 by mmostafa         ###   ########.fr       */
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
			if (recipes->curpath)
			{
				recipes->mute = 1;
				chdir_operations(recipes);
			}
			else if ((recipes->curpath = tmp))
				return (errors_container(4, recipes));
		}
	}
	else
		return (-1);
	return (0);
}
