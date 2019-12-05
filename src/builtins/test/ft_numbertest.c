/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbertest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:39:28 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/05 19:03:04 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_limit(char *nb, int sign)
{
	int		len;
	char	*max;
	int		i;
	int		n1;
	int		n2;

	max = "9223372036854775807";
	len = ft_strlen(nb);
	if (len > 19)
		return (2);
	else if (len == 19)
	{
		i = 0;
		while (i < 19)
		{
			n1 = max[i] - '0';
			n2 = nb[i] - '0';
			if (n2 > n1)
			{
				if (i == 19 && sign && n2 == 8)
					return (0);
				ft_printf("42sh: test: %s: integer expression expected\n", nb);
				return (2);
			}
			else if (n1 > n2)
				return (0);
			i++;
		}
	}
	return (0);
}

int		ft_cmp(int id, char *n1, char *n2)
{
	long long int num1;
	long long int num2;

	num1 = ft_atoi(n1);
	num2 = ft_atoi(n2);
	if (id == 18)
		return (num1 == num2 ? 0 : 1);
	if (id == 19)
		return (num1 != num2 ? 0 : 1);
	if (id == 20)
		return (num1 >= num2 ? 0 : 1);
	if (id == 21)
		return (num1 < num2 ? 0 : 1);
	if (id == 22)
		return (num1 <= num2 ? 0 : 1);
	if (id == 23)
		return (num1 > num2 ? 0 : 1);
	return (0);
}

void	ft_sign(int *n1sign, int *n2sign, char **n1, char **n2)
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
	if (**n2 == '-' || **n2 == '+')
	{
		if (**n2 == '-')
			*n2sign = 1;
		tmp = ft_strdup(*n2 + 1);
		free(*n2);
		*n2 = tmp;
	}
}

int		ft_mathcmp(int id, char *n1, char *n2)
{
	int n1signed;
	int n2signed;
	int	r;

	r = 0;
	n1 = ft_isnbr(n1);
	n2 = ft_isnbr(n2);
	if (!n1 || !n2)
	{
		ft_printf("42: test: integer expression expected\n");
		r = 2;
	}
	else
	{
		ft_sign(&n1signed, &n2signed, &n1, &n2);
		r = ft_limit(n1, n1signed);
		if (!r && ft_limit(n2, n2signed))
			r = 1;
		else if (!r)
			r = ft_cmp(id, n1, n2);
	}
	free(n1);
	free(n2);
	return (r);
}
