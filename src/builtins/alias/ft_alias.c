/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:38:24 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/03 22:30:46 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_alias(char **args)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_strpos(args[i], "=") > 0)
		{
			ft_get_kv(args[i], &key, &value);
			ft_addtohashmap(key, value, ALIAS);
			free(key);
			free(value);
		}
		else
			ft_show_aliases(args[i]);
		i++;
	}
	if (i == 0)
		ft_show_aliases(NULL);
	return (0);
}
