/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addjob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 17:49:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 10:03:42 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

int		ft_newid(void)
{
	int id;

	id = 1;
	while (ft_getjob_byindex(id))
		id++;
	return (id);
}

void	ft_addjob(t_job *job, t_container *container)
{
	t_list		*list;

	list = container->list;
	if (ft_getbypgid(list, job->pgid))
		return ;
	ft_lstadd(&container->list, ft_lstnew(job, 0));
	ft_sort(container->list);
}

void	ft_init_proc(t_process *proc)
{
	proc->exited = 0;
	proc->pid = 0;
	proc->signaled = 0;
	proc->status = 0;
	proc->stoped = 0;
}

void	ft_init_job(t_job *job)
{
	job->pgid = 0;
	job->suspended = 0;
	job->foreground = job->flag != BG;
	job->killed = 0;
	job->notified = 1;
	job->id = ft_newid();
}