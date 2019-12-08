/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:03:26 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/08 09:22:21 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_get_term(t_job *job)
{
	t_shell	*container;

	container = get_shell_cfg(0);
	ft_check_jobs_status(job);
	if (container->interractive)
	{
		tcsetattr(0, TCSANOW, ft_getset(0)->term);
		if (tcsetpgrp(0, getpgrp()) == -1)
		{
			ft_printf_fd(2, "42sh : fatal error");
			exit(1);
		}
	}
}

void	ft_wait(t_job *job)
{
	int			status;
	pid_t		pid;

	job->suspended = 0;
	if (!job->pgid)
		return ;
	if (!job->foreground)
	{
		ft_addjob(job, ft_getset(NULL));
		if (get_shell_cfg(0)->interractive)
			ft_printf("[%d] %d\n", job->id, job->pgid);
	}
	else
	{
		if (get_shell_cfg(0)->interractive)
			tcsetpgrp(0, job->pgid);
		while (1)
		{
			if ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0)
			{
				ft_change_state(job, pid, status);
				if (ft_terminated(job) || ft_stoped(job))
					break ;
			}
		}
		ft_set_last_rvalue(ft_getjobstatus(job->processes));
		ft_get_term(job);
	}
}
