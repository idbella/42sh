/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:37:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/14 21:37:23 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/ioctl.h>

int		main(int argc, char **argv, char **env)
{
	char		*line;
	t_job		*tokens;
	t_shell		shell;
	t_init		init;

	argc == 0 ? argv = NULL : 0;
	init_(&shell, env, &init);
	while (1)
	{
		if ((line = readline(&init, "\x1B[32m42sh $> \x1b[0m")) && ft_strlen(line) > 0)
		{
			if ((tokens = parse(line)))
			{
				exec(tokens);
				ft_free_job(tokens);
			}
		}
		ft_notify();
		ft_strdel(&line);
	}
}
