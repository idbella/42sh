/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:01:02 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/29 20:16:25 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_resetstatus(t_job *job)
{
	t_process	*proc;

	job->suspended = 0;
	job->foreground = 1;
	proc = job->processes;
	while (proc)
	{
		proc->stoped = 0;
		proc->signaled = 0;
		proc->status = 0;
		proc = proc->next;
	}
}

void	ft_fg(char **arg)
{
	t_job	*job;

	if (!(job = ft_getjob(*arg, "fg")))
		return ;
	ft_resetstatus(job);
	signal(SIGCHLD, SIG_DFL);
	if (!killpg(job->pgid, SIGCONT))
	{
		if (tcsetpgrp(0, job->pgid) != 0)
		{
			ft_printf("can't setpgrp :-(\n");
			return ;
		}
		ft_printf("[%d]\t+\t continued %s\n", job->id, job->command);
		ft_wait(job);
	}
	else
	{
		ft_printf("unable to continue job %s\n", job->command);
		ft_deljob(job, ft_getset(NULL));
	}
}
