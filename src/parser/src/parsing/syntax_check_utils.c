/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:11:06 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/17 15:11:18 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			correct_syntax(char *param)
{
	int		pos;
	int		i;

	pos = 0;
	i = 0;
	if (param[0] == '#')
	{
		i = 1;
		while (param[i])
		{
			if (!ft_isalnum(param[i]) && param[i] != '_')
				return (0);
			i++;
		}
	}
	else
	{
		while (param[i])
		{
			if (ft_isalnum(param[i]) || param[i] == '_' || param[i] == '?')
			{
				while (ft_isalnum(param[i]) || param[i] == '_')
					i++;
				if (param[i] && param[i] != ':' && param[i] != '#'
				&& param[i] != '-' && param[i] != '?' && param[i] != '+'
				&& param[i] != '=' && param[i] != '%')
					return (0);
				else
					return (1);
			}
			else
				return (0);
		}
	}
	return (1);
}