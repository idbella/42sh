/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:05:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/14 11:05:53 by sid-bell         ###   ########.fr       */
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

char	**ft_env(t_params *p, t_function *builtin)
{
	char	**env;
	t_list	*l;
	int		i;
	int		count;
	t_map	*mp;

	env = NULL;
	if (!builtin)
	{
		if (!p->tmpenv)
			env = ft_serialize_env(EXPORTED_ONLY);
		else
		{
			i = 0;
			count = ft_lstcount(p->tmpenv);
			env = ft_memalloc(sizeof(char *) * (count + 1));
			l = p->tmpenv;
			while (i < count)
			{
				mp = l->content;
				env[i] = ft_join("%s=%s", mp->key, mp->value);
				i++;
				l = l->next;
			}
		}
	}
	return (env);
}

int		ft_error(char *error, char *name)
{
	ft_set_last_rvalue(127);
	ft_printf_fd(2, error, name);
	return (0);
}

char	*ft_getexecutable(t_process *process)
{
	char	*file;
	char	*error;

	error = NULL;
	if ((file = ft_findfile(process->arg[0], &error, 1)))
		return (file);
	else if (!error)
		error = "42sh: %s: command not found\n";
	if (error)
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

int		ft_fork(t_params *params, t_process *process, t_function *func)
{
	char	**env;
	char	*file;
	int		rval;


	rval = 0;
	file = NULL;
	(!func) ? file = ft_getexecutable(process) : 0;
	if (!(process->pid = fork()))
	{
		ft_setup_child(params, params->job);
		if (func)
			exit(func(process->arg + 1));
		else if (file)
		{
			env = ft_env(params, func);
			execve(file, process->arg, env);
			ft_printf_fd(2, "Wrong exec format\n");
			exit(127);
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
