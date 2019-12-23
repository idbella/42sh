/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getexitcode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:57:35 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/23 14:57:50 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_sign(int *n1sign, char **n1)
{
	char	*tmp;

	if (**n1 == '-' || **n1 == '+')
	{
		if (**n1 == '-')
			*n1sign = 1;
		tmp = ft_strdup(*n1 + 1);
		free(*n1);
		*n1 = tmp;
	}
}

char	ft_exitcode(char *arg, uint8_t *code)
{
	char	*n1;
	int		n1signed;
	int		r;

	r = 0;
	n1 = ft_isnbr(arg);
	if (!n1)
	{
		ft_printf("42: exit: integer expression expected\n");
		r = 2;
	}
	else
	{
		ft_sign(&n1signed, &n1);
		*code = 255;
		if (!(r = ft_maxinteger(n1, n1signed)))
			*code = ft_atoi(n1);
	}
	free(n1);
	return (r);
}
