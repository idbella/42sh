/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:37:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/21 18:53:29 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	_init_()
{

}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	DATATYPE	tokens;

	argc = 0;
	argv = NULL;
	while (1)
	{
		line = readline("$> ", EXIT_ON_EOT);
		if ((tokens = parse(line)))
			exec(tokens);
	}
}
