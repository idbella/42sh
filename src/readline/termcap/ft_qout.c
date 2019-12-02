/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qout.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:50:54 by oherba            #+#    #+#             */
/*   Updated: 2019/12/01 21:57:45 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		ft_init_qote(t_init *init)
{
	ft_strdel(&init->out_put);
	init->s_cursor = 5;
	init->s_l = 5;
	init->s.selection = 0;
	init->out_put = ft_strdup("(qt)>");
	if (!g_sig)
		ft_putstr_fd(init->out_put, 1);
}

static char *ft_cmd_(char *str, t_init *init)
{
	char	*cmd;

	
	
	(void)str;
	cmd = ft_strtrim(init->kote);
	ft_strdel(&init->out_put);
	init->out_put = ft_strjoin("(21)>", init->kote);
	ft_strdel(&(init->kote));
	end_cursor(init);
	ft_printf("\033[%dD", init->s_col);
	//ft_add_to_history(init, 2);
	//ft_putendl(cmd);  //ft_display(cmd, init);
	return (cmd);
	ft_strdel(&cmd);
	ft_strdel(&init->out_put);
}

static char *ft_qoute__fin(char *str, t_init *init)
{
	char	*tmp;

	//init->hstry_position = NULL;
	tmp = init->kote;
	init->kote = ft_strjoin(init->kote, "\n");
	ft_strdel(&tmp);
	tmp = init->kote;
	init->kote = ft_strjoin(init->kote, &init->out_put[5]);
	ft_strdel(&tmp);
	if (ft_strchr(&init->out_put[5], init->qt))
	{
		return (ft_cmd_(str, init));
	}
	return (NULL);
}

char			*ft_qoute(char *str, t_init *init)
{
	char *line ;

	line  = NULL;
	if (!(ft_check_key(init, str)))
		return (NULL);
	else if (str[0] == 10 && ft_strlen(str) == 1)
	{
		ft_putchar('\n');
		if (ft_strcmp(&init->out_put[5], "") != 0)
		{
			if ((line = ft_qoute__fin(str, init)))
				return (line);
		}
		ft_init_qote(init);
	}
	else
		ft_str_line(str, init);
	//ft_update_tmp_hisory(init);
	return (NULL);
}
