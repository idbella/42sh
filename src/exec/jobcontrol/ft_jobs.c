/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:02:19 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/19 09:44:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

static int	ft_get_flags(char **cmd, char *flag)
{
	int		i;
	int		index;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && cmd[i][1])
		{
			index = 1;
			while (cmd[i][index])
			{
				if (cmd[i][index] == 'p')
					*flag = 'p';
				else if (cmd[i][index] == 'l')
					*flag = 'l';
				else
				{
					ft_printf_fd(2,
						"42sh: jobs: -%c: invalid option\n", cmd[i][index]);
					return (-1);
				}
				index++;
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

void	ft_printjob(t_job *job, char flag)
{
	char		sign;
	t_container	*container;

	container = ft_getset(0);
	sign = ' ';
	sign = job == container->current ? '+' : ' ';
	sign = job == container->prev ? '-' : sign;
	if (flag == 'l')
		ft_printf("[%d] %c %d %s %s\n",
				job->id,
				sign,
				job->pgid,
				job->suspended ? "Stoped" : "Running",
				job->command);
	else if (flag == 'p')
		ft_printf("%d\n", job->pgid);
	else
		ft_printf("[%d] %c %s\t\t%s\n",
				job->id,
				sign,
				job->suspended ? "Stoped" : "Running",
				job->command);
}

void	ft_printall(char flag)
{
	t_container	*container;
	t_list		*list;
	t_job		*job;

	container = ft_getset(NULL);
	//ft_lstrev(&container->list);
	list = container->list;
	while (list)
	{
		job = list->content;
		ft_printjob(job, flag);
		list = list->next;
	}
	//ft_lstrev(&container->list);
}

int		ft_jobs(char **args)
{
	char	flag;
	int		i;
	t_job	*job;
	int		rval;

	rval = 0;
	flag = 0;
	if ((i = ft_get_flags(args, &flag)) < 0)
		return (1);
	if (args[i])
	{
		while (args[i])
		{
			if ((job = ft_getjob(args[i], "jobs")))
				ft_printjob(job, flag);
			else
				rval = 1;
			i++;
		}
	}
	else
		ft_printall(flag);
	return (rval);
}
