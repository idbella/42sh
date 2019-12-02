/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:37:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 20:15:20 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	// char		*line;
	// t_job		*tokens;
	// // t_shell		shell;
	 t_init  	init;

	// env = NULL;
	// argc = 0;
	// argv = 0;
	// // init_(&shell, env, &init);
	// ft_init_readline(&init);
	// while (1)
	// {
	// 	line = readline(&init);
	// 		// dprintf(open("/dev/ttys014",O_RDWR),"\nstr = %s\n", line);
	// 	if ((tokens = parse(line)))
	// 		printf("token kayn\n");
	// 		// exec(tokens);
	// 	// ft_notify();
	// }
	//t_init init;
	char	*line = NULL;
	
	ft_init_readline(&init);
	while (42)
	{
		//ft_putendl_fd(line, 2);
		if ((line = readline(&init)))
		{
		
			// dprintf(open("/dev/ttys012",O_RDWR),"\nstr = %s\n", line);
			ft_init_output(&init);
			;//ft_putendl_fd(line, 2);
		}

	}
	return (0);
}
