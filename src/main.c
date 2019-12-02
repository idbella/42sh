/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:37:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 14:24:35 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		main(int argc, char **argv, char **env)
{
	char		*line;
	t_job		*tokens;
	t_shell		shell;

	argc = 0;
	argv = 0;
	init_(&shell, env);
	while (1)
	{
		line = readline("$> ", EXIT_ON_EOT);
		if (ft_strequ("exit", line))
			exit(0);
		if ((tokens = parse(line)))
			exec(tokens);
		ft_notify();
		free(line);
	}
}
