/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 01:04:33 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/08 09:39:24 by sid-bell         ###   ########.fr       */
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
		if (params->forkbuiltins)
			return (ft_fork(params, cmd, func));
		else
			return (func(cmd->arg + index + 1));
	}
	else
		return (ft_fork(params, cmd, NULL));
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

void	ft_free_tmp_env(t_list *lst)
{
	t_map	*mp;
	t_list	*next;

	while (lst)
	{
		mp = lst->content;
		free(mp->key);
		free(mp->value);
		next = lst->next;
		free(mp);
		free(lst);
		lst = next;
	}
}

int		ft_getinterns(t_params *params, t_process *cmd)
{
	char	**argv;
	int		i;
	char	type;
	int		status;

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
			status = ft_run(params, cmd);
			ft_free_tmp_env(params->tmpenv);
			params->tmpenv = NULL;
		}
		i++;
	}
	return (0);
}
