/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:09:56 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/20 14:47:28 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_test(char **args)
{
	char	*oper;
	char	*l_oper;
	char	*r_oper;
	int		id;
	int		test[8];

	oper = NULL;
	l_oper = NULL;
	r_oper = NULL;
	if (!args[0])
		return (1);
	if (!args[1])
		return (0);
	if (ft_strequ(args[0], "!"))
	{
		id = ft_test(args + 1);
		if (id == 1 || id == 0)
			return (!id);
		return (2);
	}
	ft_setoprations(test);
	if (ft_getoprators(args, &l_oper, &oper, &r_oper))
		return (2);
	if (!r_oper && oper)
	{
		r_oper = oper;
		oper = l_oper;
		l_oper = NULL;
	}
	if (!(id = ft_getoperator_id(oper, (l_oper && r_oper) ? BINARY : UNARY)))
		return (2);
	if (id < 8)
		return (ft_eval(id, r_oper, test));
	if (id == 10 || id == 9)
		return (ft_usergroup(id, r_oper));
	if (id == 11 || id == 12 || id == 13)
		return (ft_rwx(id, r_oper));
	if (id == 14)
		return (ft_sizetest(r_oper));
	if (id < 18)
		return (ft_strtest(id, l_oper, r_oper));
	return (ft_mathcmp(id, l_oper, r_oper));
}
