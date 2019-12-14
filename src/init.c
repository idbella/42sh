/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:12:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/14 14:39:17 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_sigint_handler(int sig)
{
	sig = 0;
	ft_putstr("\n$> ");
}

t_shell	*get_shell_cfg(t_shell *new)
{
	static t_shell	*sh;

	if (new)
		sh = new;
	return (sh);
}

void	init_(t_shell *shell, char **env, t_init *init)
{
	signal(SIGINT, ft_sigint_handler);
	get_shell_cfg(shell);
	shell->interractive = 1;
	ft_init_exec();
	ft_init_builtins(env);
	ft_init_readline(init);
	ft_read_file_(init);
	ft_addtohashmap("FCEDIT", "vim", INTERN);
	shell->init = init;
	shell->last_exit = 0;
	shell->subshell = 0;
}
