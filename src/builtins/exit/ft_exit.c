/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:28:12 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/15 18:07:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	ft_isnumber(char *str)
{
	int num;

	num = 0;
	while (*str)
	{
		num = 1;
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (num);
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

size_t	ft_arraylen(char **ptr)
{
	size_t	size;

	size = 0;
	while (ptr[size])
		size++;
	return (size);
}

int		ft_exit(char **argv)
{
	t_container		*container;
	uint8_t			r;

	container = ft_getset(NULL);
	if (ft_arraylen(argv) > 1)
	{
		ft_printf("42sh: exit: too many arguments\n");
		return (1);
	}
	if (!ft_status(container->list) && container->time_to_exit)
	{
		ft_printf("There are stopped jobs\n");
		container->time_to_exit = 0;
		return (1);
	}
	else
	{
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
