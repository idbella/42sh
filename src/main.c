/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:37:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 12:15:15 by sid-bell         ###   ########.fr       */
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
		if ((tokens = parse(line)))
			exec(tokens);
	}
}
