/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:41:50 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/14 11:06:18 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_run_fc_editor(char **args)
{
	t_params	p;
	t_job		*job;

	if (!args || !args[0])
		return (1);
	p.pipe_stdin = -1;
	p.tmpenv = NULL;
	job = ft_newjob(0, 0);
	job->processes->arg = args;
	job->command = ft_strdup(args[0]);
	p.job = job;
	if (ft_fork(&p, job->processes, NULL))
		return (1);
	ft_wait(job);
	return (ft_getjobstatus(job->processes));
}
