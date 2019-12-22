/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:54:19 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/22 18:16:23 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	recipes_preparations(t_recipes *recipes)
{
	recipes->oldpwd = ft_getenv("OLDPWD");
	recipes->home = ft_getenv("HOME");
	recipes->pwd = get_shell_cfg(0)->pwd; 
	recipes->cdpath = ft_getvlaue_bykey("CDPATH", INTERN);
	recipes->curpath = NULL;
	recipes->options = 0;
	recipes->mute = 0;
}

char	check_param_for_cd(char *param)
{
	int		i;

	i = 0;
	if (param[i] == '-')
		i++;
	while (param[i] == 'L' || param[i] == 'P')
		i++;
	if (param[i - 1] != 'P' && param[i - 1] != 'L')
		return (0);
	return (param[i - 1]);
}
