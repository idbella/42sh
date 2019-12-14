/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qout.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:50:54 by oherba            #+#    #+#             */
/*   Updated: 2019/12/13 21:30:17 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_init_qote(t_init *init)
{
	//ft_strdel(&init->out_put);
	init->s_cursor = (int)ft_strlen(init->promt);
	init->s_l = (int)ft_strlen(init->promt);
	init->s.selection = 0;
	init->out_put = ft_strdup(init->promt);
	if (!g_sig && init->qoute == 1)
		ft_putstr_fd(init->out_put, 1);
}

static char *ft_cmd_( t_init *init)
{
	char	*cmd;
	
	cmd = ft_strtrim(init->kote);
	ft_strdel(&init->out_put);
	init->qoute = 0;
	init->qt = '\0';
	init->out_put = ft_strjoin(init->promt, init->kote);
	ft_strdel(&(init->kote));
	// end_cursor(init);
	// ft_printf("\033[%dD", init->s_col);
	return (cmd);
	ft_strdel(&cmd);
	ft_strdel(&init->out_put);
}

 char *ft_qoute__fin( t_init *init)
{
	char	*tmp;

	tmp = init->kote;
	
	init->kote = ft_strjoin(init->kote, "\n");
	ft_strdel(&tmp);
	tmp = init->kote;
	init->kote = ft_strjoin(init->kote, &init->out_put[(int)ft_strlen(init->promt)]);
	ft_strdel(&tmp);
		// dprintf(open("/dev/ttys006",O_RDWR),"str = |%s|	\n", init->kote);
	if (ft_strchr(&init->out_put[(int)ft_strlen(init->promt)], init->qt))
	{	
		return (ft_cmd_( init));
	}
		///readline_(init, init->promt);
	return (NULL);
}

char			*ft_qoute(char *str, t_init *init)
{
	char *line ;

	line  = NULL;
	if (!(ft_check_key(init, str)))
		return (NULL);
 if (str[0] == 10 && ft_strlen(str) == 1)
	{
		ft_putchar('\n');
		if (ft_strcmp(&init->out_put[(int)ft_strlen(init->promt)], "") != 0)
		{
			if ((line = ft_qoute__fin(init)))
				return (ft_check_qout(line, init));
		}
		ft_init_qote(init);
	}
	else
	{	
		ft_str_line(str, init);
	}	
	return (NULL);
}
