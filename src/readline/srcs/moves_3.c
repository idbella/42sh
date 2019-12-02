/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 23:04:20 by oherba            #+#    #+#             */
/*   Updated: 2019/12/01 21:57:45 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	ft_mini_alt_down(int *x, int *a, t_init *init)
{
	if (init->out_put[init->s_cursor] == '\n')
	{
		*x = get_strat(init, init->s_cursor - 1);
		*a = 1;
	}
	else
		*x = get_strat(init, init->s_cursor);
}

void	ft_alt_down(int *x, int *a, t_init *init)
{
	if ((get_end(init, init->s_cursor) +
		get_strat(init, init->s_cursor)) != init->s_l + 1)
	{
		ft_mini_alt_down(x, a, init);
		if (*x == 0)
			ft_move(init, "+", 1);
		if (init->s_cursor < init->s_col &&
				get_strat(init, init->s_cursor) == init->s_cursor + 1)
			*x = *x - 5;
		while (init->out_put[init->s_cursor] != '\n' &&
				init->s_cursor < init->s_l && *x != 0)
			ft_move(init, "+", 1);
		if (*x)
			*x += *a;
		*a = 0;
		while (init->out_put[init->s_cursor + 1] != '\n' &&
				init->s_cursor < init->s_l && *x > 0)
		{
			(*x)--;
			ft_move(init, "+", 1);
		}
		if (init->out_put[init->s_cursor + 1] == '\n')
			ft_move(init, "+", 1);
	}
}

void	ft_alt_up_3(int *x1, t_init *init)
{
	if (init->out_put[init->s_cursor] == '\n')
	{
		*x1 = get_strat(init, init->s_cursor - 1);
		ft_move(init, "-", *x1);
	}
	else
	{
		*x1 = get_strat(init, init->s_cursor);
		ft_move(init, "-", *x1 - 1);
	}
}

void	ft_alt_up(int *x, int *x1, int *a, t_init *init)
{
	if ((get_end(init, init->s_cursor) +
				get_strat(init, init->s_cursor)) != init->s_l + 1)
	{
		ft_alt_up_2(x, a, init);
		ft_alt_up_3(x1, init);
		if (init->s_cursor < init->s_col &&
				get_strat(init, init->s_cursor) ==
				init->s_cursor + 1 && *x != 0)
			ft_move(init, "+", 5);
		if (*x)
			*x += *a;
		*a = 0;
		while (init->out_put[init->s_cursor] != '\n' &&
				init->s_cursor >= 5 && *x > 1 && *x != 0)
		{
			(*x)--;
			ft_move(init, "+", 1);
		}
	}
}
