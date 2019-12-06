/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isintern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 00:33:51 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/06 09:49:02 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	ft_str_isalnum(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str))
			return (0);
		str++;
	}
	return (1);
}

char	ft_isintern(char *cmd)
{
	char	*key;
	char	*value;

	if (!ft_strchr(cmd, '='))
		return (0);
	ft_get_kv(cmd, &key, &value);
	if (ft_isdigit(key[0]) && key[1] && ft_isalphanum(key + 1))
		return (0);
	return (ft_str_isalnum(key));
}
