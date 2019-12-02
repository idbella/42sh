/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:04:30 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 19:49:48 by sid-bell         ###   ########.fr       */
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

t_job	*ft_newjob(pid_t pid, int flag)
{
	t_job *jb;

	jb = ft_memalloc(sizeof(t_job));
	jb->flag = flag;
	jb->next = NULL;
	jb->pgid = pid;
	jb->processes = ft_memalloc(sizeof(t_process));
	jb->processes->heredoc = NULL;
	jb->processes->next = NULL;
	ft_init_job(jb);
	jb->processes->pid = pid;
	return (jb);
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

int		ft_status(t_process *pr)
{
	int status;

	status = 0;
	while (pr)
	{
		if (pr->pid > 0)
			status = pr->status;
		else
			status = 0;
		pr = pr->next;
	}
	return (status);
}

void	ft_execbg(t_job *job)
{
	pid_t		pid;
	t_job		*jb;
	int			status;

	if (!(pid = fork()))
	{
		ft_resetsignals();
		pid = getpid();
		setpgid(pid, pid);
		get_shell_cfg(0)->interractive = 0;
		ft_getset(0)->list = NULL;
		job = ft_list(job->processes);
		status = exec(job);
		exit(status ? 127 : 0);
	}
	setpgid(pid, pid);
	jb = ft_newjob(pid, 0);
	jb->pgid = pid;
	ft_printf("[%d] %d\n", jb->id, jb->pgid); 
	jb->command = job->command;
	ft_addjob(jb, ft_getset(0));
	ft_getset(NULL)->current = jb;
}

int		exec(t_job *job)
{
	t_params	p;
	int			status;
	int			flag;
	int			rval;

	p.fd = 1;
	rval = 0;
	ft_getset(0)->params = &p;
	while (job)
	{
		p.pipe_stdin = -1;
		p.job = job;
		p.forkbuiltins = 0;
		ft_init_job(job);
		if (job->flag == BG && ft_run_in_sub(job->processes))
			ft_execbg(job);
		else
		{
			p.forkbuiltins = job->flag == BG;
			rval = ft_exec_job(&p, job->processes);
			ft_wait(job);
			if (job->flag == OR || job->flag == AND)
			{
				status = ft_status(job->processes);
				flag = job->flag;
				while (job && ((job->flag == AND && status) || (job->flag == OR && !status)))
					job = job->next;
			}
		}
		job = job->next;
	}
	ft_getset(0)->params = NULL;
	return (rval);
}