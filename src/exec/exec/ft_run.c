/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:05:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 20:02:41 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_free_array(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_setup_child(t_params *params, t_job *job)
{
	t_shell	*sh;

	sh = get_shell_cfg(0);
	sh->jobs = NULL;
	sh->interractive = 0;
	if (params->pipe_stdin >= 0)
		close(params->pipe_stdin);
	ft_jobs_in_child(job);
}

void	ft_fork(t_params *params, char *file, t_process *process, t_function *func)
{
	char	**env;
	pid_t	pid;

	env = NULL;
	if (!func)
		env = ft_serialize_env(EXPORTED_ONLY);
	pid = fork();
	if (!pid)
	{
		ft_setup_child(params, params->job);
		if (func)
			func(process->arg + 1);
		else
		{
			execve(file, process->arg + params->argv_index, env);
			ft_printf_fd(2, "Wrong exec format\n");
			exit(1);
		}
		exit(0);
	}
	process->pid = pid;
	if (!params->job->pgid)
		params->job->pgid = pid;
	setpgid(pid, params->job->pgid);
	ft_free_array(env);
}

int		ft_error(char *error, char *name)
{
	//ft_set_last_rvalue(127);
	ft_printf_fd(2, error, name);
	return (0);
}

int		ft_run(t_params *params, t_process *process)
{
	char	*file;
	char	*error;

	error = NULL;
	if ((file = ft_findfile(process->arg[params->argv_index], &error)))
		ft_fork(params, file, process, NULL);
	else if (!error)
		error = "42sh: %s: command not found\n";
	if (error)
		ft_error(error, process->arg[params->argv_index]);
	free(file);
	return (1);
}
