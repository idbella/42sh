/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isintern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 00:33:51 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/07 10:41:16 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	ft_isintern(char *cmd)
{
	char	*key;
	char	*value;

	if (!ft_strchr(cmd, '='))
		return (0);
	ft_get_kv(cmd, &key, &value);
	if (ft_isdigit(key[0]) && key[1] && ft_isalphanum(key + 1))
		return (0);
	return (1);
}
