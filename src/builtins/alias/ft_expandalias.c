/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expandalias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:48:22 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/03 19:10:44 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_replace(t_process *proc, t_map *alias, int index)
{
	char			*val;
	t_job			*job;

	val = alias->value;
	if ((job = parse(val)))
		ft_insert_at(job, proc, index);
	else
		return (0);
	return (1);
}

char	ft_in_cycle(char *key)
{
	t_list	*lst;
	char	*k;

	lst = ft_getset(0)->last_aliases;
	while (lst)
	{
		k = lst->content;
		if (ft_strequ(k, key))
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	ft_addalias(t_map *alias, t_process *proc, int i)
{
	t_list	*node;

	node = ft_lstnew(alias->key, ft_strlen(alias->key));
	ft_lstadd(&ft_getset(0)->last_aliases, node);
	return (ft_replace(proc, alias, i));
}

int	ft_handle_alias(t_job *job)
{
	t_map		*alias;
	t_process	*proc;
	int			i;
	char		**argv;

	proc = job->processes;
	while (proc)
	{
		argv = proc->arg;
		i = 0;
		ft_getset(0)->last_aliases = NULL;
		while (argv[i])
		{
			if (!ft_isintern(proc->arg[i]))
			{
				if ((alias = ft_getbykey(argv[i], ALIAS)))
					if (!ft_in_cycle(alias->key))
						if (!ft_addalias(alias, proc, i))
							return (0);
				break ;
			}
			i++;
		}
		proc = proc->next;
	}
	return (1);
}
