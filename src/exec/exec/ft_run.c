/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:05:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/15 16:04:53 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_setup_child(t_params *params, t_job *job)
{
	ft_getset(0)->list = NULL;

	if (params->pipe_stdin >= 0)
		close(params->pipe_stdin);
	ft_jobs_in_child(job);
}

int		ft_error(char *error, char *name)
{
	ft_set_last_rvalue(127);
	ft_printf_fd(2, error, name);
	return (0);
}

char	*ft_getexecutable(t_process *process, int report)
{
	char	*file;
	char	*error;

	error = NULL;
	if ((file = ft_findfile(process->arg[0], &error, 1)))
		return (file);
	else if (!error)
		error = "42sh: %s: command not found\n";
	if (error && report)
		ft_error(error, process->arg[0]);
	return (NULL);
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

	if (process->ass[0])
	{
		i = 0;
		while (process->ass[i])
		{
			ft_get_kv(process->ass[i], &key, &val);
			if (key && ft_strequ(key, "PATH"))
				return (1);
			i++;
		}
	}
	return (0);
}

int		ft_fork(t_params *params, t_process *process, t_function *func)
{
	char	**env;
	char	*file;
	int		rval;

	rval = 0;
	file = NULL;
	if (!params->forkbuiltins && params->job->foreground && !ft_path_changed(process))
		ft_getexecutable(process, 0);
	if (!(process->pid = fork()))
	{
		ft_setup_child(params, params->job);
		ft_redirect(process->redir);
		ft_getinterns(process, ENV_ENTRY);
		(!func) ? file = ft_getexecutable(process, 1) : 0;
		if (func)
			exit(func(process->arg + 1));
		else if (file)
		{
			env = ft_serialize_env(EXPORTED_ONLY);
			execve(file, process->arg, env);
			ft_printf_fd(2, "Wrong exec format\n");
		}
		exit(127);
	}
	else if (process->pid < 0)
		rval = 1;
	else
		ft_joingroup(params, process);
	free(file);
	return (rval);
}
