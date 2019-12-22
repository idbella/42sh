/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 04:41:44 by oherba            #+#    #+#             */
/*   Updated: 2019/12/22 22:15:47 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			ft_catch_sig(int a)
{
	a = 0;
	g_sig = 1;
	get_shell_cfg(0)->init->heredoc_int = 0;
	ft_putchar('\n');
	ft_strdel(&get_shell_cfg(0)->init->promt);
	get_shell_cfg(0)->init->promt = ft_strdup("$> ");
	ft_putstr("$> ");
}

char			*readline(t_init *init, char *promt)
{
	char		buffer[8];
	int			position;
	char		*line;

	line = NULL;
	ft_strdel(&init->promt);
	init->promt = ft_strdup(promt);
	ft_init_terminal();
	ft_init_output(init);
	while (1)
	{
		ft_bzero(buffer, 8);
		if (!(position = read(0, buffer, 6)) && !init->skip_read)
			continue;
		if (g_sig_win)
			ft_size_terminal(init);
		buffer[position] = '\0';
		if ((line = ft_take_move(init, buffer, position)))
		{
			tcsetattr(0, TCSANOW, &init->term_copy);
			return (line);
		}
	}
	return (NULL);
}

void			ft_catch_sig_window(int a)
{
	a = 0;
	g_sig_win = 1;
}

void			ft_initial_main(t_init *init)
{
	g_sig = 0;
	tcgetattr(0, &init->term_copy);
	ft_putstr("\033[H\033[J");
	init->out_put = ft_strnew(0);
	init->promt = ft_strnew(0);
	init->kote = NULL;
	init->str_search = ft_strnew(0);
	ft_size_terminal(init);
	init->auto_comlpetion = 0;
	init->completion_lst_position = NULL;
	init->completion_lst = NULL;
	ft_add_history_(init, "", 0);
	get_shell_cfg(0)->init = init;
	get_shell_cfg(0)->init->history_postoin = NULL;
}

void			ft_init_readline(t_init *init)
{
	char		*name;

	signal(SIGINT, ft_catch_sig);
	signal(SIGWINCH, ft_catch_sig_window);
	if (!(name = getenv("TERM")))
		exit(1);
	if (!(tgetent(NULL, name)))
		exit(1);
	ft_memset((void *)init, '\0', sizeof(t_init));
	ft_initial_main(init);
}
