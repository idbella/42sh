/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:37:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/22 18:32:33 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	*get_shell_cfg(t_shell *new)
{
	static	t_shell	*sh = NULL;

	if (new)
		sh = new;
	return (NULL);
}

void	init_(t_shell *shell, char **env)
{
	(void)env;
	get_shell_cfg(shell);
	shell->last_exit = 0;
}

int		main(int argc, char **argv, char **env)
{
	char		*line;
	DATATYPE	tokens;
	t_shell		shell;

	argc = 0;
	argv = NULL;
	init_(&shell, env);
	while (1)
	{
		line = readline("$> ", EXIT_ON_EOT);
		if ((tokens = parse(line)))
			exec(tokens);
	}
}
