/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:39:10 by oherba            #+#    #+#             */
/*   Updated: 2019/12/01 21:57:46 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		ft_size_terminal(t_init *init)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	init->s_col = w.ws_col;
}

void		ft_putstr_nbr(char *str, int s_t, int e_d)
{
	tputs(tgetstr("mr", NULL), 0, my_putchar);
	ft_putstr("\x1B[32m");
	while (s_t < e_d)
	{
		ft_putchar_fd(str[s_t], 1);
		s_t++;
	}
	tputs(tgetstr("me", NULL), 0, my_putchar);
}

void		ft__nbr_putstr(char *str, int s_t, int e_d)
{
	while (s_t < e_d)
	{
		ft_putchar_fd(str[s_t], 1);
		s_t++;
	}
}

void		ft_put_move(t_init *init, int i)
{
	while (i > 5)
	{
		i--;
		if (init->out_put[(i)] == '\n')
		{
			ft_printf("\033[%dA", 1);
			if ((get_strat(init, i - 1)))
				ft_printf("\033[%dC", (get_strat(init, i - 1)) % init->s_col);
		}
		else if ((get_strat(init, i + 1) - 1) % init->s_col == 0)
			ft_printf("\033[%dA\033[%dC", 1, init->s_col);
		else
			tputs(tgetstr("le", NULL), 0, my_putchar);
	}
}

void		ft_put_clor(t_init *init, char *str)
{
	int i;

	(void)str;
	i = 0;
	if (init->s_cursor == init->s.s_t)
		return ;
	i = init->s_cursor;
	tputs(tgetstr("sc", NULL), 0, my_putchar);
	ft_put_move(init, i);
	if (init->s.s_t < init->s_cursor && init->s_cursor <= init->s_l)
	{
		ft__nbr_putstr(init->out_put, 5, init->s.s_t);
		ft_putstr_nbr(init->out_put, init->s.s_t, init->s_cursor);
		ft_putstr_fd(&init->out_put[init->s_cursor], 1);
	}
	else if (init->s.s_t > init->s_cursor && init->s_cursor >= 5)
	{
		ft__nbr_putstr(init->out_put, 5, init->s_cursor);
		ft_putstr_nbr(init->out_put, init->s_cursor, init->s.s_t);
		ft_putstr_fd(&init->out_put[init->s.s_t], 1);
	}
	tputs(tgetstr("rc", NULL), 0, my_putchar);
}
