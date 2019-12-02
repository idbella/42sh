/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 22:21:30 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/01 22:22:57 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		main()
{
	t_init init;
	char	*line = NULL;
	
	ft_init_readline(&init);
	while (42)
	{
		//ft_putendl_fd(line, 2);
		if ((line = readline(&init)))
		{
		
			dprintf(open("/dev/ttys012",O_RDWR),"\nstr = %s\n", line);
			ft_init_output(&init);
			;//ft_putendl_fd(line, 2);
		}

	}
	return (0);
}
