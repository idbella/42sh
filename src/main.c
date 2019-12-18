/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:37:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/18 10:35:17 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/ioctl.h>
#include <time.h>

int		main(int argc, char **argv, char **env)
{
	char		*line;
	t_job		*jobs;
	t_shell		shell;
	t_init		init;
	char		*prompt;

	argc == 0 ? argv = NULL : 0;
	init_(&shell, env, &init);
	while (1)
	{
		prompt = ft_getprompt();
		if ((line = readline(&init, prompt)) && ft_strlen(line) > 0)
		{
			free(prompt);
			if ((jobs = parse(line)))
			{
				exec(jobs);
				ft_free_job(jobs);
			}
		}
		ft_notify();
		ft_strdel(&line);
	}
}
