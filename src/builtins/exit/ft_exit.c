/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:28:12 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 17:11:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

void		ft_freemap(void)
{
	ft_empty(ANYHASH);
	free(get_shell_cfg(0)->hashmap);
}

size_t		ft_arraylen(char **ptr)
{
	size_t	size;

	size = 0;
	while (ptr[size])
		size++;
	return (size);
}

int			ft_init_exit(char **argv)
{
	t_container		*container;
	t_list			*lst;
	t_list			*next;

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
	lst = container->list;
	while (lst)
	{
		next = lst->next;
		ft_free_job(lst->content);
		free(lst);
		lst = next;
	}
	return (0);
}

int			ft_exit(char **argv)
{
	uint8_t			r;

	if (ft_init_exit(argv))
		return (1);
	else
	{
		ft_free_array(ft_getset(0)->test_operators);
		ft_freemap();
		r = 0;
		if (argv[0] && !ft_isnumber(argv[0]) && (r = 255))
			ft_printf_fd(2, "42sh: exit: numeric argument required\n");
		else if (argv[0])
			r = ft_atoi(argv[0]);
		ft_free_job(ft_getset(0)->jobs);
		free(ft_getset(0));
		//free(get_shell_cfg(0)->pwd);
		exit(r);
	}
	return (0);
}
