/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_wheels.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:59:01 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/25 11:57:38 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		cd_wheels(t_recipes *recipes)
{
	if (recipes->curpath)
	{
		recipes->second_curpath = cdpath_concatenation(recipes->cdpath,
									recipes->curpath);
		recipes->error = chdir_operations(recipes);
		if (recipes->error)
		{
			if (!recipes->second_curpath)
				return (errors_container(recipes->curpath, recipes->error));
			recipes->tmp = recipes->curpath;
			recipes->curpath = recipes->second_curpath;
			if (chdir_operations(recipes))
			{
				ft_strdel(&recipes->curpath);
				ft_strdel(&recipes->cwd);
				return (errors_container(recipes->tmp, recipes->error));
			}
			ft_strdel(&recipes->curpath);
			ft_strdel(&recipes->tmp);
			return (0);
		}
		ft_strdel(&recipes->curpath);
		return (0);

	}
	return (-1);
}
