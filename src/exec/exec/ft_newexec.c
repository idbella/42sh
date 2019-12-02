/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:05:30 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 19:51:19 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_pipe(int *pipefd, t_process *process)
{
	pipefd[0] = -1;
	pipefd[1] = -1;
	ft_restorestd(0, 1, 1);
	if ((process->flag == PIPE && process->next) || process->heredoc)
	{
		pipe(pipefd);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	return (pipefd[0]);
}

int		ft_printheredoc(t_process *process)
{
	if (process->heredoc)
	{
		ft_printf_fd(1, "%s\n", process->heredoc);
		free(process->heredoc);
		process->heredoc = NULL;
		return (1);
	}
	return (0);
}

char	ft_init_run(t_params *params, t_process *process)
{
	t_function *func;
	t_process	*p;

	p = params->job->processes;
	if ((func = ft_is_builtin(process->arg[0])))
	{
		if ((p && p->next) || params->forkbuiltins)
			ft_fork(params, process, func);
		else
			func(process->arg + 1);
		return (1);
	}
	else if (ft_isintern(process->arg[0]))
	{
		return (ft_getinterns(params, process));
	}
	ft_fork(params, process, NULL);
	return (1);
}

char	ft_exec_job(t_params *params, t_process *process)
{
	int			fds[2];
	char		status;

	fds[0] = dup(0);
	status = 1;
	while (process)
	{
		params->argv_index = 0;
		params->tmpenv = NULL;
		ft_init_proc(process);
		dup2(fds[0], 0);
		close(fds[0]);
		params->pipe_stdin = ft_pipe(fds, process);
		if (process->heredoc || ft_redirect(params->fd, process->redir))
		{
			if (ft_printheredoc(process))
				continue ;
			if (process->arg && process->arg[0])
				status = ft_init_run(params, process);
		}
		else
			status = 0;
		process = process->next;
	}
	ft_restorestd(1, 1, 1);
	return (status);
}
