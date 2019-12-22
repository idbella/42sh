/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:05:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 12:30:07 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_setup_child(t_params *params, t_job *job, t_process *process)
{
	if (!ft_redirect(process->redir))
		exit(1);
	if (!process->arg)
		exit(0);
	ft_getinterns(process, ENV_ENTRY);
	ft_getset(0)->list = NULL;
	ft_getset(0)->current = NULL;
	ft_getset(0)->prev = NULL;
	if (params->fdscopy[0] > 2)
		close(params->fdscopy[0]);
	if (params->fdscopy[1] > 2)
		close(params->fdscopy[1]);
	if (params->pipe_stdin >= 0)
		close(params->pipe_stdin);
	ft_jobs_in_child(job);
}

void	ft_joingroup(t_params *params, t_process *process)
{
	pid_t pid;

	pid = process->pid;
	if (!params->job->pgid)
		params->job->pgid = pid;
	if (get_shell_cfg(0)->interractive)
		setpgid(pid, params->job->pgid);
}

int		ft_path_changed(t_process *process)
{
	int		i;
	char	*key;
	char	*val;

	if (process->ass)
	{
		i = 0;
		while (process->ass[i])
		{
			ft_get_kv(process->ass[i], &key, &val);
			free(val);
			if (key && ft_strequ(key, "PATH"))
			{
				free(key);
				return (1);
			}
			free(key);
			i++;
		}
	}
	return (0);
}

void	ft_execute(char *file, t_process *process, t_params *p)
{
	char **env;

	env = ft_serialize_env(EXPORTED_ONLY);
	execve(file, process->arg, env);
	free(file);
	ft_free_array(env);
	ft_printf_fd(2, "Wrong exec format\n");
	ft_free_job(p->job);
}

int		ft_fork(t_params *params, t_process *process, t_function *func)
{
	char	*file;
	int		rval;

	rval = 0;
	file = NULL;
	if (process->arg && !params->forkbuiltins &&
		params->job->foreground && !ft_path_changed(process))
		free(ft_getexecutable(process, 0));
	if (!(process->pid = fork()))
	{
		ft_setup_child(params, params->job, process);
		(!func) ? file = ft_getexecutable(process, 1) : 0;
		if (func)
			exit(func(process->arg + 1));
		else if (file)
			ft_execute(file, process, params);
		exit(127);
	}
	else if (process->pid < 0)
		rval = 1;
	else
		ft_joingroup(params, process);
	free(file);
	return (rval);
}
