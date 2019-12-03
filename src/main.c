/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:37:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/03 20:59:05 by yelazrak         ###   ########.fr       */
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
			ft_add_history_(&init, line);
			if ((tokens = parse(line)))
			{
				exec(tokens);
				ft_free_job(tokens);
			}
		}
		ft_notify();
		ft_init_output(&init);
		ft_strdel(&line);
	}
}
