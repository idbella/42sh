/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:54:19 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/23 16:58:08 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	recipes_preparations(t_recipes *recipes)
{
	recipes->oldpwd = ft_getenv("OLDPWD");
	recipes->home = ft_getenv("HOME");
	recipes->cwd =	getcwd(NULL, 0);
	recipes->pwd = get_shell_cfg(0)->pwd;
	recipes->cdpath = ft_getvlaue_bykey("CDPATH", INTERN);
	recipes->curpath = NULL;
	recipes->options = 0;
	recipes->mute = 0;
}
