/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:05:30 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/17 20:44:09 by sid-bell         ###   ########.fr       */
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
	t_function	*func;
	t_process	*p;
	int			type;

	p = params->job->processes;
	if ((func = ft_is_builtin(process->arg[0])))
	{
		if ((p && p->next) || params->forkbuiltins)
			return (ft_fork(params, process, func));
		else
		{
			ft_redirect(process->redir);
			return (func(process->arg + 1));
		}
	}
	if (process->ass[0])
	{
		type = process->arg[0] ? ENV_ENTRY : INTERN_ENTRY;
		if (type == INTERN_ENTRY && !params->forkbuiltins && params->job->foreground)
		{
			ft_getinterns(process, INTERN_ENTRY);
			return (0);
		}
	}
	return (ft_fork(params, process, NULL));
}

void	ft_readfile(t_params *params)
{
	char		*line;
	t_process	*proc;

	if (!params->job->processes->next)
	{
		proc = params->job->processes;
		if (proc->redir->file && proc->redir->type == O_RDONLY)
		{
			while (get_next_line(0, '\n', &line) > 0)
				ft_printf_fd(1, "%s\n", line);
		}
	}
}

char	ft_exec_job(t_params *params, t_process *process)
{
	int			fds[2];
	char		status;

	fds[0] = -1;
	params->fdscopy[0] = dup(1);
	params->fdscopy[1] = dup(2);
	status = 0;
	while (process)
	{
		ft_init_proc(process);
		if (fds[0] > 0)
		{
			dup2(fds[0], 0);
			close(fds[0]);
		}
		params->pipe_stdin = ft_pipe(fds, process, params->fdscopy);
		if (process->heredoc)
		{
			ft_printheredoc(process);
			continue ;
		}
		if (process->arg[0] || process->ass[0])
			status = ft_init_run(params, process);
		else if (get_shell_cfg(0)->subshell)
			ft_readfile(params);
		process = process->next;
	}
	if (!isatty(params->fdscopy[0]) && get_shell_cfg(0)->subshell)
	{
		dup2(params->fdscopy[0], 1);
		ft_restorestd(1, 0, 1);
	}
	else
		ft_restorestd(1, 1, 1);
	if (params->fdscopy[0] > 2)
		close(params->fdscopy[0]);
	if (params->fdscopy[0] > 2)
		close(params->fdscopy[1]);
	return (status);
}
