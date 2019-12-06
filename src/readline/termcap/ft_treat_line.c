/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:21:04 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/05 15:08:43 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		del_char_of_line(char **line, t_init *init)
{
	char	*t_line;
	char	*t_2_line;

	t_line = *line;
	if (!(init->s_l > 5 && init->s_cursor > 5))
		return ;
	ft_move(init, "-", 1);
	(init->s_cursor)++;
	t_2_line = ft_strsub(t_line, 0, init->s_cursor - 1);
	*line = ft_strjoin(t_2_line, &t_line[init->s_cursor]);
	tputs(tgetstr("sc", NULL), 0, my_putchar);
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	ft_putstr_fd(&t_line[init->s_cursor], 1);
	tputs(tgetstr("rc", NULL), 0, my_putchar);
	(init->s_l)--;
	(init->s_cursor)--;
	ft_strdel(&t_2_line);
	ft_strdel(&t_line);
}

void		ft_init_output(t_init *init)
{
	ft_strdel(&init->out_put);
	init->s_cursor = 5;
	init->s_l = 5;
	// init->redict = NULL;
	init->skip_read = 0;
	// init->s_line = 0;
	init->qoute = 0;
	init->qt = '\0';
	init->heredoc_int = 0;
	init->key = NULL;
	if (!(init->heredoc_str))
		init->heredoc_str = ft_strnew(0);
	init->s.selection = 0;
	init->out_put = ft_strdup("(42)>");
	if (!g_sig)
		ft_putstr_fd(init->out_put, 1);
}

static void	ft_key__65(char *str, t_init *init)
{
	(void)str;
	(void)init;
	if (init->history_postoin == NULL && init->last_history != NULL)
		init->history_postoin = init->last_history;
	else if (init->history_postoin && init->history_postoin->prvet!= NULL)
		init->history_postoin = init->history_postoin->prvet;
	if (init->history_postoin)
	{
		home_cursor(init);
		ft_printf("\033[%dD", 5);
		if (init->heredoc_int)
			ft_init_heredoc(init);
		else if (init->qoute == 1)
			ft_init_qote(init);
		else
			ft_init_output(init);
		tputs(tgetstr("cd", NULL), 0, my_putchar);
		ft_str_line(init->history_postoin->str, init);
	}
}

static void	ft_key__66(char *str, t_init *init)
{
	(void)str;
	(void)init;
	
	if (init->history_postoin != NULL && init->history_postoin)
		init->history_postoin = init->history_postoin->next;
	home_cursor(init);
	ft_printf("\033[%dD", 5);
	if (init->heredoc_int)
		ft_init_heredoc(init);
	else if (init->qoute == 1)
		ft_init_qote(init);
	else
		ft_init_output(init);
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	if (init->history_postoin)
		ft_str_line(init->history_postoin->str, init);
	//  else if (init->history_postoin->next)
	//  	ft_cat_string_of_line(init, &init->hstry_tmp[5]);
}

int			key_4_of_cursor(char *str, t_init *init)
{
	if (str[2] == 65)
	{
		ft_key__65(str, init);
		return (1);
	}
	if (str[2] == 67)
	{
		if (init->s_l > init->s_cursor)
			ft_move_mul_line(init, "+");
		return (1);
	}
	if (str[2] == 66)
	{
		ft_key__66(str, init);
		return (1);
	}
	if (str[2] == 68)
	{
		if (init->s_cursor > 5)
			ft_move_mul_line(init, "-");
		return (1);
	}
	return (0);
}
