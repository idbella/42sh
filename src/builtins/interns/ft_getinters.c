/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 01:04:33 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 08:33:38 by sid-bell         ###   ########.fr       */
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

int		ft_run(t_params *params, t_process *cmd)
{
	t_function	*func;
	int			index;

	index = params->argv_index;
	if ((func = ft_is_builtin(cmd->arg[index])))
	{
		if (params->job->processes->next)
			ft_fork(params, cmd, func);
		else
			func(cmd->arg[index]);
	}
	else
		ft_fork(params, cmd, NULL);
	return (0);
}

void	ft_addintern(t_params *params, char *str, int type)
{
	char	*key;
	char	*value;

	ft_get_kv(str, &key, &value);
	if (type == ENV_ENTRY)
		ft_add_to_tmp_map(params, key, value);
	else
		ft_addtohashmap(key, value, INTERN);
}

int		ft_getinterns(t_params *params, t_process *cmd)
{
	char	**argv;
	int		i;
	char	type;

	type = ft_kv_type(cmd->arg);
	argv = cmd->arg;
	i = 0;
	params->tmpenv = NULL;
	if (type == ENV_ENTRY)
		ft_cpyenv(params);
	while (argv[i])
	{
		if (ft_isintern(argv[i]))
		{
			ft_addintern(params, argv[i], type);
		}
		else
		{
			params->argv_index = i;
			return (ft_run(params, cmd));
		}
		i++;
	}
	return (1);
}