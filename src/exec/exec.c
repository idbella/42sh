/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:04:30 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/07 19:42:45 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_init_exec()
{
	ft_init_jobcontrol();
}

char	ft_run_in_sub(t_process *p)
{
	while(p)
	{
		if (p->flag == OR || p->flag == AND)
			return (1);
			p = p->next;
	}
	return (0);
}

t_job	*ft_list(t_process *pr)
{
	t_job		*job;
	t_job		*new;
	t_job		*head;

	job = NULL;
	head = NULL;
	while (pr)
	{
		new = ft_newjob(0, 0);
		new->flag = pr->flag;
		new->processes->arg = pr->arg;
		new->command = pr->arg[0];
		if (job)
			job->next = new;
		else
			head = new;
		job = new;
		pr = pr->next;
	}
	return (head);
}

void	ft_execbg(t_job *job)
{
	pid_t		pid;
	t_job		*jb;

	if (!(pid = fork()))
	{
		ft_resetsignals();
		pid = getpid();
		setpgid(pid, pid);
		get_shell_cfg(0)->interractive = 0;
		ft_getset(0)->list = NULL;
		job = ft_list(job->processes);
		exit(exec(job));
	}
	setpgid(pid, pid);
	jb = ft_newjob(pid, 0);
	jb->pgid = pid;
	ft_printf("[%d] %d\n", jb->id, jb->pgid); 
	jb->command = job->command;
	ft_addjob(jb, ft_getset(0));
}



int		exec(t_job *job)
{
	t_params	p;
	uint8_t		status;
	int			flag;

	p.fd = 1;
	status = 0;
	ft_getset(0)->params = &p;
	ft_getset(0)->last_aliases = NULL;
	while (job)
	{
		p.pipe_stdin = -1;
		p.tmpenv = NULL;
		p.job = job;
		ft_init_job(job);
		if (job->flag == BG && ft_run_in_sub(job->processes))
			ft_execbg(job);
		else
		{
			p.forkbuiltins = job->flag == BG || job->processes->next;
			signal(SIGCHLD, SIG_DFL);
			status = ft_exec_job(&p, job->processes);
			ft_wait(job);
			signal(SIGCHLD, ft_sigchld);
			status = !status ? ft_getjobstatus(job->processes) : status;
			if (job->flag == OR || job->flag == AND)
			{
				flag = job->flag;
				while (job && ((job->flag == AND && status) || (job->flag == OR && !status)))
					job = job->next;
			}
		}
		job = job->next;
	}
	ft_getset(0)->params = NULL;
	return (status);
}