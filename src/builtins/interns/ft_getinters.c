/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 01:04:33 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 18:22:03 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#define ENV_ENTRY 1
#define INTEREN_ENTRY 2

char	ft_kv_type(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (!ft_isintern(argv[i]))
			return (ENV_ENTRY);
		i++;
	}
	return (INTEREN_ENTRY);
}

int		ft_rrun(t_params *params, t_process *process)
{
	t_function	*func;
	int			index;

	index = params->argv_index;
	if ((func = ft_is_builtin(process->arg[index])))
		func(process->arg + 1);
	else
		return (ft_run(params, process));
	return (0);
}

void	ft_addintern(t_params *params, char *str, int type)
{
	char	*key;
	char	*value;

	ft_get_kv(str, &key, &value);
	ft_addtohashmap(key, value, INTERN)->exported = 1;
}

int		ft_getinterns(t_params *params, t_process *process)
{
	char	**argv;
	int		i;
	char	type;

	type = ft_kv_type(process->arg);
	params->tmpenv = ft_cpyenv();
	argv = process->arg;
	i = 0;
	while (argv[i])
	{
		if (ft_isintern(argv[i]))
		{
			ft_addintern(params, argv[i], type);
		}
		else
		{
			params->argv_index = i;
			return (ft_rrun(params, process));
		}
		i++;
	}
	return (1);
}
