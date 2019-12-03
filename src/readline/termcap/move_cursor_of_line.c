/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_of_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:20:17 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/03 21:13:25 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			my_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}


int			get_end(t_init *init, int e_d)
{
	int		i;
	int 	a;

	i = 0;
	a = 0;
	while (e_d < init->s_l)
	{
		if (init->out_put[e_d] == '\t')
		{
			a = ft_tab_(init, e_d - 1);
			i += a;
		}

		if (init->out_put[e_d] == '\n')
		{
			return (i);
		}
		if (!a)
			i++;
		e_d++;
	}
	return (i);
}

static char  *ft_cmd_mangement__(char *str, t_init *init)
{
	char	*cmd;


	(void)str;
	cmd = ft_strtrim(&init->out_put[5]);
	end_cursor(init);
	ft_printf("\033[%dD", init->s_col);
	return (cmd);
}

char		*move_cursor_and_mangemant_fonction(char *str,
		t_init *init)
{
	int i;
	char	*line;

	i = 0;

	if (!(ft_check_key(init, str)))
		return (NULL);
	else if (str[0] == 10 && ft_strlen(str) == 1)
	{
		// if (ft_strcmp(&init->out_put[5], "") != 0)
		//ft_refrech(init);
		ft_putchar('\n');
			if ((line = ft_cmd_mangement__(str, init)))
				return (line);
	}
	else
		ft_str_line(str, init);
	return (NULL);
}
