/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_of_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:20:17 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/22 08:45:08 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int my_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}
int ft_cke_c_eskip(int i, char *str)
{
	int j;

	j = 0;
	while (i >= 0)
	{
		if (str[i] == '\\')
			j++;
		else
			return (((j % 2) == 0) ? 1 : 0);
		i--;
	}
	return (((j % 2) == 0) ? 1 : 0);
}

int get_end(t_init *init, int e_d)
{
	int i;
	int a;

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
			return (i);
		if (!a)
			i++;
		e_d++;
	}
	return (i);
}

static char *ft_cmd_mangement__(char *str, t_init *init)
{
	char *cmd;

	(void)str;
	cmd  = NULL;
	if (init->esq == 1)
	{
		cmd = ft_strjoin(init->kote, &init->out_put[(int)ft_strlen(init->promt)]);
		ft_strdel(&init->kote);
		init->esq = 0;
	}
	else
		cmd = ft_strdup(&init->out_put[(int)ft_strlen(init->promt)]);
	end_cursor(init);
	ft_printf("\033[%dD", init->s_col);
	return (cmd);
}

char *call_qote(t_init *init, char c)
{
	init->qt = c;
	init->kote = ft_strdup(&init->out_put[(int)ft_strlen(init->promt)]);
	ft_strdel(&init->promt);
	init->promt = ft_strdup("(qout)>");
	init->qoute = 1;
	ft_init_qote(init);
	return (NULL);
}

char *call_esqp(char *str, t_init *init)
{
	int i;

	i = ft_strlen(str) - 1;
	if (str[i] == '\\' && str[i + 1] == '\0' && ft_cke_c_eskip(i - 1, str))
		str[i] = '\0';
	init->kote = ft_strdup(str);
	ft_strdel(&init->promt);
	init->promt = ft_strdup("> ");
	init->esq = 1;
	ft_strdel(&str);
	ft_init_output(init);
	return (NULL);
}
char *ft_get_search(t_init *init, char *str)
{
	t_history *lst;

	lst = init->last_history;
	if (str == NULL || str[0] == '\0')
		return ("");
	while (lst)
	{
		if (ft_strstr(lst->str, str))
			return (lst->str);
		lst = lst->prvet;
	}
	return ("");
}
void ft_search_init(t_init *init)
{
	init->search = 0;
	home_cursor(init);
	ft_printf("\033[%dD", init->s_col);
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	ft_strdel(&init->promt);
	init->promt = ft_strdup("$> ");//ft_getprompt();
	ft_strdel(&init->out_put);//
	init->out_put = ft_strjoin(init->promt, init->str_search);
	init->s_cursor = ft_strlen(init->out_put);
	init->s_l = ft_strlen(init->out_put);
	ft_putstr(init->out_put);
}
char *ft_search_(char *str, t_init *init)
{
	if ((!(ft_check_key(init, str))) || ((str[0] == 10 && ft_strlen(str) == 1)))
		ft_search_init(init);
	else
	{
		tputs(tgetstr("cd", NULL), 0, my_putchar);
		ft_str_line(str, init);
		tputs(tgetstr("sc", NULL), 0, my_putchar);
		ft_strdel(&init->str_search);
		init->str_search = ft_strdup(ft_get_search(init, &init->out_put[(int)ft_strlen(init->promt)]));
		ft_putstr(" : `");
		ft_putstr(init->str_search);
		ft_putchar('`');
		tputs(tgetstr("rc", NULL), 0, my_putchar);
	}
	return (NULL);
}
char *ft_check_qout(char *str, t_init *init)
{
	int i;
	char c;

	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if ((str[i] == '"' && ft_cke_c_eskip(i - 1, str)) ||\
		 (str[i] == '\'' && ft_cke_c_eskip(i - 1, str)))
		{
			c = str[i++];
			while (str[i] != c && str[i])
				i++;
			if (str[i] != c)
			{
				ft_strdel(&str);
				return (call_qote(init, c));
			}
		}
		else if ((((str[i] == '\\' && ft_cke_c_eskip(i - 1, str))) || str[i] == '|'\
		 || (i > 0 && str[i - 1] == '&' && str[i] == '&')) && str[i + 1] == '\0')
			return (ft_check_qout(call_esqp(str, init), init));
	}
	return (str);
}

int 	ft_searh_(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '!' &&  str[i + 1] != ' ' && str[i + 1] != '\t' && str[i+ 1] != '\0')
		return (1);
		i++;
	}
	return (0);	
}
char *move_cursor_and_mangemant_fonction(char *str,
										 t_init *init)
{
	char *line;

	line = NULL;
	if (!(ft_check_key(init, str)))
		return (NULL);
	if (str[0] == 9)
	{
		ft_autocomplete_42(init);
		return (NULL);
	}	
	else if (str[0] == -62 && str[1] == -82)
	{
		init->search = 1;
		home_cursor(init);
		ft_printf("\033[%dD", init->s_col);
		tputs(tgetstr("cd", NULL), 0, my_putchar);
		return (readline(init, "(reverse-i-search)> "));
	}
	else if (str[0] == 10 && ft_strlen(str) == 1)
	{
		ft_putchar('\n');
		line = ft_cmd_mangement__(str, init);
		if (line && ft_searh_(line))
		{
			if ((line = ft_expansion(init, line)))
			{
				ft_init_output(init);
				ft_str_line(line, init);
				ft_strdel(&line);
				return (NULL);
			 }
		}
		
		if (line && ft_strncmp(line, "fc", 2) != 0)
			ft_add_history_(init, line, 1);
		return (ft_check_qout(line, init) );	
	}
	else
		ft_str_line(str, init);
	ft_add_history_(init, &init->out_put[(int)ft_strlen(init->promt)], 0);
	return (NULL);
}
