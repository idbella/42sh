/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 01:09:38 by oherba            #+#    #+#             */
/*   Updated: 2019/12/22 22:16:14 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_check_key(t_init *init, char *str)
{
	if (g_sig)
	{
		ft_init_output(init);
		g_sig = 0;
		return (0);
	}
	if (((str[0] == -30) || (str[0] == -61)) &&
	key_slect(str, init) != 0 && init->heredoc_int != 1)
	{
		ft_exec_ket_s(init);
		return (0);
	}
	if ((str[0] == 27) && (str[1] == 91) && key_4_of_cursor(str, init) != 0)
		return (0);
	return (1);
}
