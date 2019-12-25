/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_wheels.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:59:01 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/25 09:43:09 by mmostafa         ###   ########.fr       */
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
				ft_strdel(&tmp);
				return (chdir_operations(recipes));
			}
			return (-1);
		}
		ft_strdel(&recipes->curpath);
		ft_strdel(&recipes->cwd);
		return (0);
	}
	return (-1);
}
