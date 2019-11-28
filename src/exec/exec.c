/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:04:30 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/25 15:29:49 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_wait(t_job *job)
{
	t_process *proc;

	proc = job->processes;
	while (proc)
	{
		waitpid(proc->pid, NULL, 0);
		proc = proc->next;
	}
}

void	ft_run(t_job *job)
{
	t_process	*proc;
	int			pfd[2];
	int			save;

	save = dup(0);
	pfd[0] = -1;
	proc = job->processes;
	while (proc)
	{
		if (pfd > 0)
		{
			dup2(pfd[0], 0);
			close(pfd[0]);
		}
		if (proc->next)
		{
			pipe(pfd);
			dup2(pfd[1], 1);
			close(pfd[1]);
		}
		else
			dup2(save, 1);
		if (!(proc->pid = fork()))
		{
			if (job->pgid == -1)
				setpgid(getpid(), getpid());
			execvp(proc->arg[0], proc->arg);
			perror("exec : ");
			exit(0);
		}
		if (job->pgid == -1)
			job->pgid = proc->pid;
		setpgid(job->pgid, proc->pid);
		proc = proc->next;
	}
	dup2(save, 0);
	if (job->flag != BG)
		ft_wait(job);
}

int		exec(DATATYPE job)
{
	t_process	*proc;
	pid_t		pid;

	while (job)
	{
		job->pgid = -1;
		if (job->flag == BG)
		{
			proc = job->processes;
			while (proc)
			{
				if (proc->flag == OR || proc->flag == AND)
				{
					if (!(pid = fork()))
					{
						ft_run(job);
						exit(1);
					}
					break;
				}
				proc = proc->next;
			}
		}
		ft_run(job);
		job = job->next;
	}
	return (0);
}