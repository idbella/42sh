/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 01:13:38 by oherba            #+#    #+#             */
/*   Updated: 2019/12/03 21:27:53 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	ft_vide__line(t_init *init)
{
	int		i;

	i = init->s_cursor;
	end_cursor(init);
	ft_printf("\033[%dB\033[%dA", 1, 1);
	home_cursor(init);
	ft_move(init, "+", i - 5);
	ft_refrech(init);
}

static void	ft_move__(t_init *init, char *str)
{
	(void)str;
	if (init->s_cursor != init->s_l)
	{
		if (get_end(init, init->s_cursor) == 0 &&
				(get_strat(init, init->s_cursor - 1) + 1) % (init->s_col) == 0)
			ft_vide__line(init);
		else if (get_end(init, init->s_cursor) != 0 &&
				get_end(init, init->s_cursor) != 0 &&
				(get_end(init, init->s_cursor) + get_strat(init,
				init->s_cursor)) % (init->s_col) == 0)
			ft_vide__line(init);
	}
}

int			ft_cat_of_line(char *str, t_init *init)
{
	char	*line;
	char	*temp;
	char	*t_line;

	if (init->out_put == NULL)
		init->out_put = ft_strnew(0);
	line = init->out_put;
	temp = ft_strsub(line, 0, init->s_cursor);
	t_line = ft_strjoin(temp, str);
	ft_strdel(&temp);
	init->out_put = ft_strjoin(t_line, &init->out_put[init->s_cursor]);
	ft_strdel(&t_line);
	ft_strdel(&line);
	init->s_cursor += ft_strlen(str);
	init->s_l = ft_strlen(init->out_put);
	return (0);
}

void		ft_str_line(char *str, t_init *init)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	j = 0;
	
	 if (str[0] == 9)
	 	return ;
	// 	ft_autocomplete(init, env);
	//else
	
	 if (str[0] == 127)
		del_char_of_line(&init->out_put, init);
	else if (str && ft_strcmp(str, ""))
	{
	 if (str[0] == -30 && str[1] == -128 && str[2] == -96)
	 {
		 str[0] = '\t';
		 str[1] = '\0';
	 }	
		while (str[j])
		{			
			if (ft_isprint(str[j]) || str[j] == '\n' || str[j] == '\t')
			   {
		
					tmp = ft_strsub(str, j, 1);
					ft_cat_string_of_line(init, tmp);
					ft_strdel(&tmp);
				}
				
			j++;
		}
	}
}


int			ft_tab_(t_init *init, int e_d)
{
	int i;

	i = 0;
	int a;

	a = (get_strat(init, e_d) - 1) % init->s_col;
	//if (a == 0)
	a = e_d - a ;//+ 1;
	while (a <= e_d)//3///0
	{
		if ((init->out_put[e_d] == '\n') || init->out_put[e_d] == '\t')
		{
			return ( 8 - (i % 8));
		}
		i++;
		e_d--;
	}
	{
		//dprintf(open("/dev/ttys015",O_RDWR),"nbr = %d\n",get_strat(init, e_d));
	}
	return ( 8 - (i % 8));
}

void		ft_cat_string_of_line(t_init *init, char *str)
{
	char	*tmp;

	tmp = NULL;
	ft_move__(init, str);
	ft_cat_of_line(str, init);
	//dprintf(open("/dev/ttys003",O_RDWR),"i = %d 	s_l = %d  cursor = %d, col = %d\n", 99, init->s_l, init->s_cursor,init->s_col);
	tputs(tgetstr("sc", NULL), 0, my_putchar);
	//if (init->s_cursor != init->s_l)
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	tmp = ft_strdup(&init->out_put[init->s_cursor - ft_strlen(str)]);
	ft_putstr_fd(tmp, 1);
	ft_strdel(&tmp);
	if (init->s_cursor != init->s_l)
	{
		tputs(tgetstr("rc", NULL), 0, my_putchar);
		tputs(tgetstr("nd", NULL), 0, my_putchar);
		if (init->out_put[(init->s_cursor)] == '\n')
		{
			if ((get_strat(init, init->s_cursor - 1)) % (init->s_col) == 0)
				ft_printf("\033[%dB\033[%dD", 1, init->s_col - 1);
		}
		// else if (init->out_put[init->s_cursor - 2] == '\t' && (get_strat(init, init->s_cursor) - 2) % init->s_col == 0)//
		// ft_printf("\033[%dB\033[%dD", 1, init->s_col - 1);	////
	}
	if ((get_strat(init, init->s_cursor) - 1) % init->s_col == 0)
			ft_printf("\033[%dB\033[%dD", 1, init->s_col - 1);
	//dprintf(open("/dev/ttys004",O_RDWR),"\nba3edd 0get__ = %d 		get_end_ = %d	\n",(get_strat(init, init->s_cursor)), get_end(init, init->s_cursor));
	
	//ft_refrech(init);
	
}
