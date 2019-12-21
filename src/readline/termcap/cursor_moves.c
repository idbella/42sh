/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:34:50 by oherba            #+#    #+#             */
/*   Updated: 2019/12/16 21:09:32 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		home_cursor(t_init *init)
{
	while (init->s_cursor > (int)ft_strlen(init->promt))
		ft_move(init, "-", 1);
}

void		end_cursor(t_init *init)
{
	while (init->s_cursor < init->s_l)
		ft_move(init, "+", 1);
}

void		home_cursor_2(t_init *init)
{
	//dprintf(open("/dev/ttys002", O_RDWR),"str = |%s|	\n","jhgjhfjg");
		//dprintf(open("/dev/ttys002",O_RDWR),"str = |%s|		len = |%d| \n",init->promt, (int)ft_strlen(init->promt));

	if (init->s_cursor > (int)ft_strlen(init->promt) && init->out_put[init->s_cursor - 1] == '\n')
		ft_move(init, "-", 1);
	while (init->s_cursor > (int)ft_strlen(init->promt) && init->out_put[init->s_cursor - 1] != '\n')
		ft_move(init, "-", 1);
}

void		end_cursor_2(t_init *init)
{
	if (init->s_cursor < init->s_l && init->out_put[init->s_cursor] == '\n')
		ft_move(init, "+", 1);
	while (init->s_cursor < init->s_l && init->out_put[init->s_cursor] != '\n')
		ft_move(init, "+", 1);
}
