/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mul_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 11:58:05 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/05 14:48:06 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			line_lfet(t_init *init, int e_d)
{
	int		i;
	int		a;

	i = 0;
	a = e_d;
	while (5 <= e_d && i < init->s_col)
	{
		if (e_d == 5)
			return (a + 1);
		if (init->out_put[e_d] == '\n')
			return (i);
		i++;
		e_d--;
	}
	return (-1);
}

int			get_strat(t_init *init, int e_d)
{
	int i;
	int a;
	int j;
	int k;

	i = 0;
	a = 0;
	k = 0;
	j = e_d;
	while (0 < j && init->out_put[j] != '\n')
		j--;
	while (j <= e_d)
	{
		if (init->out_put[j] == '\t')
		{
			if (((init->s_col - (k % init->s_col)) % init->s_col) > 7)
				a = ( 8 - (((k) % init->s_col) % 8));
			else
			{
				if (((init->s_col - (k % init->s_col)) % init->s_col) > 0)
					a = ((init->s_col - (k % init->s_col)) % init->s_col) - 1;
				else
					a = ((init->s_col - (k % init->s_col)) % init->s_col);
			}
			
			i += a;
			k += a;
			a = 1;
		}
		if (!a)
		{
			i++;
			k++;
		}
		a = 0;
		j++;
	}
	return (i);
}

static void	ft_move__r(t_init *init, char *str)
{
	(init->s_cursor)++;	
	dprintf(open("/dev/ttys013",O_RDWR),"++++  c = |%c|		yas = %d,  col = %d 	tab = %d\n", 
	(init->out_put[(init->s_cursor)]) ,get_strat(init, init->s_cursor) , init->s_col,
		ft_tab_(init, init->s_cursor));
	if (init->out_put[(init->s_cursor - 1)] == '\t')
	{	
			 ft_printf("\033[%dC",ft_tab_(init, init->s_cursor - 2));
	}
	else if (init->out_put[(init->s_cursor - 1)] == '\n')
		ft_printf("\033[%dB\033[%dD",
				1, (get_strat(init, init->s_cursor - 2)) % init->s_col);
	else if ((get_strat(init, init->s_cursor) - 1) % init->s_col == 0)
		ft_printf("\033[%dB\033[%dD", 1, init->s_col - 1);
	else
		tputs(tgetstr("nd", NULL), 0, my_putchar);
	if (init->s.selection == 1)
		ft_put_clor(init, str);
}

void		ft_move_mul_line(t_init *init, char *str)
{
	if (ft_strcmp(str, "+") == 0)
		ft_move__r(init, str);
	else if (ft_strcmp(str, "-") == 0)
	{
		(init->s_cursor)--;
		if (init->out_put[(init->s_cursor)] == '\t')
		{
			
			dprintf(open("/dev/ttys013",O_RDWR),"------yas = %d,  col = %d 	tab = %d\n", (get_strat(init, init->s_cursor )  ) , init->s_col,
		ft_tab_(init, init->s_cursor));
			ft_printf("\033[%dD",ft_tab_(init, init->s_cursor - 1));
		}
		else if (init->out_put[(init->s_cursor)] == '\n')
		{
			ft_printf("\033[%dA", 1);
			if ((get_strat(init, init->s_cursor - 1)))
				ft_printf("\033[%dC",
						(get_strat(init, init->s_cursor - 1)) % init->s_col);
		}
		else if ((get_strat(init, init->s_cursor + 1) - 1) % init->s_col == 0)
			ft_printf("\033[%dA\033[%dC", 1, init->s_col);
		else
			tputs(tgetstr("le", NULL), 0, my_putchar);
		if (init->s.selection == 1)
			ft_put_clor(init, str);
	}
}
