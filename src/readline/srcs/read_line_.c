/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 04:41:44 by oherba            #+#    #+#             */
/*   Updated: 2019/12/06 11:17:13 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	ft_catch_sig(int a)
{
	a = 0;
	g_sig = 1;
	ft_putstr("\n(42)>");
}

char		*readline(t_init *init)
{
	char			buffer[9];
	int				position;
	char    		*line;

	line = NULL;
	while (1)
	{
		if (!(position = read(0, buffer, 4)) && !init->skip_read)
		{
			//ft_printf("pos = %d\n", position);
			continue ;
		}
	
		if (g_sig_win)
			ft_size_terminal(init);
		buffer[position] = '\0';
		int i = 0;
		//dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\n**************\n");
		while (buffer[i])
		{
			//dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\n/////--%d---/////\n", buffer[i]);
			i++;
		}
		//dprintf(open("/dev/ttys003",O_WRONLY|O_RDONLY),"\n**************\n");
		if ((line = ft_take_move(init, buffer, position)))
			return (line);
	}
	return (NULL);
}

void	ft_catch_sig_window(int a)
{
	a = 0;
	g_sig_win = 1;
}


void	ft_initial_main(t_init *init)
{
	g_sig = 0;
	tcgetattr(0, &init->term_copy);
	ft_init_terminal();
	ft_putstr("\033[H\033[J");
	init->out_put = ft_strnew(0);
	init->history_postoin = NULL;
	ft_init_output(init);
	ft_size_terminal(init);
	init->auto_comlpetion = 0;
	init->completion_lst_position = NULL;
	init->completion_lst = NULL;
	ft_add_history_(init, "", 0);
	
}


void		ft_init_readline(t_init *init)
{
	char			*name;

	signal(SIGINT, ft_catch_sig);
	signal(SIGWINCH, ft_catch_sig_window);
	if (!(name = getenv("TERM")))
		exit(1);
	if (!(tgetent(NULL, name)))
		exit(1);
	ft_memset((void *)init, '\0', sizeof(t_init));
	ft_initial_main(init);
}



