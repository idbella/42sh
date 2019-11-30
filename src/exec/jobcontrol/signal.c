/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 23:03:34 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/30 20:40:42 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

char	*ft_stopped_action(t_job *job, t_job *current)
{
	t_container *container;
	char		*st;

	container = ft_getset(0);
	st = ft_join("[%d] + Stopped %s\n", job->id, job->command);
	ft_addjob(job, container);
	(job == current) ? container->current = job : 0;
	return (st);
}

void	ft_check_job(t_job *job, t_job *current, t_container *container)
{
	int			status;
	char		*st;
	t_process	*proc;

	st = NULL;
	if (job->notified)
		return ;
	proc = job->processes;
	while (proc->next)
		proc = proc->next;
	status = proc->status;
	if (ft_terminated(job))
	{
		if (job != current || proc->signaled)
			st = ft_join("[%d] + %s %s\n", job->id,
				ft_strsignal(WTERMSIG(status)), job->command);
	}
	else if (!job->killed && ft_stoped(job))
		st = ft_stopped_action(job, current);
	if (st)
		ft_lstadd(&container->notify, ft_lstnew(st, 0));
	job->notified = 1;
	if (job == current)
		ft_set_last_rvalue(WEXITSTATUS(status));
	if (job->killed)
		ft_deljob(job, container);
}

void	ft_check_jobs_status(t_job *current)
{
	t_list		*list;
	t_job		*job;
	t_container	*container;

	container = ft_getset(NULL);
	if (current)
		ft_check_job(current, current, container);
	list = container->list;
	while (list)
	{
		job = list->content;
		if (job)
			ft_check_job(job, current, container);
		list = list->next;
	}
}

void	ft_sigchld(int sig)
{
	int		status;
	pid_t	pid;

	while (sig == SIGCHLD)
	{
		if ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0)
			ft_change_state(NULL, pid, status);
		else
			break ;
	}
	ft_check_jobs_status(NULL);
}
