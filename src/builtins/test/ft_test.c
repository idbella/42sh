/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:09:56 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/04 18:02:24 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_getoper(char *oper)
{
	char	**ops;
	int		i;

	ops = ft_strsplit("\127,-b,-c,-d,-e,-f,-L,-p,-S,\
-u,-w,-x,-z,=,!=,-eq,-ne,-ge,-lt,-le,!,-g,-r,-s", ',');
	i = 0;
	while (ops[i])
	{
		if (ft_strequ(ops[i], oper))
			return (i);
		i++;
	}
	ft_printf_fd(2, "42sh: test: file: binary operator expected\n");
	return (0);
}

int		ft_getops(char **args, char **l_oper, char **oper, char **r_oper)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (!*l_oper)
			*l_oper = args[i];
		else if (!*oper)
			*oper = args[i];
		else if (!*r_oper)
			*r_oper = args[i];
		else
		{
			ft_printf_fd(2, "42sh: test: too many arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int		ft_eval(int id, char *file, int *test)
{
	struct stat	st;
	int			i;

	i = 0;
	if (!lstat(file, &st))
	{
		if (test[id - 1])
		{
			i = ((st.st_mode & S_IFMT) == test[id - 1]) ? 0 : 1;
			return (i);
		}
		return (0);
	}
	return (12);
}

static void	ft_fill(int *test)
{
	test[0] = S_IFBLK;
	test[1] = S_IFCHR;
	test[2] = S_IFDIR;
	test[3] = 0;
	test[4] = S_IFREG;
	test[5] = S_IFLNK;
	test[6] = S_IFIFO;
	test[7] = S_IFSOCK;
}

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
	ft_fill(test);
	if (ft_getops(args, &l_oper, &oper, &r_oper))
		return (1);
	if (!r_oper)
	{
		r_oper = oper;
		oper = l_oper;
	}
	if (!(id = ft_getoper(oper)))
		return (1);
	//ft_printf("%s %d %s\n", l_oper, id, r_oper);
	if (id < 8)
		return (ft_eval(id, r_oper, test));
	return (0);
}
