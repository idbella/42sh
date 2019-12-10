/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:37:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/08 20:07:37 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		if ((line = readline(&init)))
		{
			tcsetattr(0, TCSANOW, &init.term_copy);
			if ((tokens = parse(line)))
			{
				exec(tokens);
				ft_free_job(tokens);
			}
		}
		ft_notify();
		ft_init_output(&init);
		ft_strdel(&line);
		ft_init_terminal();
	}
}
