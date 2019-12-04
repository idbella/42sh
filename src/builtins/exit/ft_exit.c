/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:28:12 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/04 10:36:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	ft_isnumber(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static char	ft_status(t_list *lst)
{
	t_job *job;

	while (lst)
	{
		job = lst->content;
		if (job->suspended)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void	ft_freemap(void)
{
	ft_empty(ANYHASH);
	free(get_shell_cfg(0)->hashmap);
}

int		ft_exit(char **argv)
{
	t_container		*container;
	uint8_t	r;

	if (get_shell_cfg(0)->interractive)
		ft_printf("exit\n");
	container = ft_getset(NULL);
	if (!ft_status(container->list) && container->time_to_exit)
	{
		ft_printf("There are stopped jobs\n");
		container->time_to_exit = 0;
		return (1);
	}
	else
	{
		tcsetattr(0, TCSANOW, ft_getset(0)->term);
		ft_freemap();
		r = 0;
		if (argv[0] && !ft_isnumber(argv[0]) && (r = 255))
			ft_printf_fd(2, "42sh: exit: numeric argument required\n");
		else if (argv[0])
			r = ft_atoi(argv[0]);
		exit(r);
	}
	return (0);
}
