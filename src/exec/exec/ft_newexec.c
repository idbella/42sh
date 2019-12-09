/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:05:30 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/08 21:25:26 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_pipe(int *pipefd, t_process *process, int *fd)
{
	pipefd[0] = -1;
	pipefd[1] = -1;

	dup2(fd[0], 1);
	dup2(fd[1], 2);
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

int		ft_init_run(t_params *params, t_process *process)
{
	t_function *func;
	t_process	*p;

	p = params->job->processes;
	if ((func = ft_is_builtin(process->arg[0])))
	{
		if ((p && p->next) || params->forkbuiltins)
			return (ft_fork(params, process, func));
		else
			return (func(process->arg + 1));
	}
	else if (ft_isintern(process->arg[0]))
		return (ft_getinterns(params, process));
	return (ft_fork(params, process, NULL));
}

char	ft_exec_job(t_params *params, t_process *process)
{
	int			fds[2];
	char		status;
	int			cpy[2];

	fds[0] = dup(0);
	cpy[0] = dup(1);
	cpy[1] = dup(2);
	status = 0;
	while (process)
	{
		params->argv_index = 0;
		ft_init_proc(process);
		dup2(fds[0], 0);
		close(fds[0]);
		params->pipe_stdin = ft_pipe(fds, process, cpy);
		if (process->heredoc || ft_redirect(params->fd, process->redir))
		{
			if (ft_printheredoc(process))
				continue ;
			if (process->arg && process->arg[0])
				status = ft_init_run(params, process);
			else if (!get_shell_cfg(0)->interractive)
			{
				
				if (!params->job->processes->next)
				{
					char *line;
					// if (process->redir->file && process->redir->type & O_RDONLY)
					// {
						
						while (get_next_line(0, '\n', &line) > 0)
						{
							ft_printf_fd(1, "%s\n", line);
						}
					// }
					// else
					// 	ft_printf("false\n");
				}
			}
		}
		else
			status = 1;
		process = process->next;
	}
	close(cpy[0]);
	close(cpy[1]);
	ft_restorestd(1, 1, 1);
	return (status);
}
