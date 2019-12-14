/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 01:04:33 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/14 11:49:19 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_run(t_params *params, t_process *cmd)
{
	t_function	*func;

	if ((func = ft_is_builtin(cmd->arg[0])))
	{
		if (params->forkbuiltins)
			return (ft_fork(params, cmd, func));
		else
			return (func(cmd->arg + 1));
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

int		ft_getinterns(t_params *params, t_process *cmd, char type)
{
	char	**assign;
	int		i;
	int		status;

	assign = cmd->ass;
	i = 0;
	params->tmpenv = NULL;
	if (type == ENV_ENTRY)
		ft_cpyenv(params);
	while (assign[i])
	{
		ft_addintern(params, assign[i], type);
		i++;
	}
	status = 0;
	if (type == ENV_ENTRY)
		status = ft_run(params, cmd);
	ft_free_tmp_env(params->tmpenv);
	params->tmpenv = NULL;
	return (status);
}
