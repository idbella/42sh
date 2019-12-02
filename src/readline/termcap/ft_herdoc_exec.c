/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 01:09:38 by oherba            #+#    #+#             */
/*   Updated: 2019/12/01 22:18:46 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			ft_check_key(t_init *init, char *str)
{
	if (g_sig)
	{
		ft_init_output(init);
		g_sig = 0;
	}
	if (((str[0] == -30) || (str[0] == -61)) && key_slect(str, init) != 0)
	{
		ft_exec_ket_s(init);
		return (0);
	}
	if ((str[0] == 27) && (str[1] == 91) && key_4_of_cursor(str, init) != 0)
		return (0);
	return (1);
}

void		ft_init_heredoc(t_init *init)
{
	
	ft_strdel(&init->out_put);
	init->s_cursor = 5;
	init->s_l = 5;
	//init->s_line = 0;
	init->s.selection = 0;
	init->out_put = ft_strdup("(hr)>");
	if (!g_sig)
		ft_putstr_fd(init->out_put, 1);
}

static char	*ft_heredoc_help_(char *str, t_init *init)
{
	char *tmp_hstry;

	ft_putchar('\n');
	//(void)env;
	//tmp_hstry = NULL;
//	tmp_hstry = init->hstry_herdog;
	//init->hstry_herdog = ft_strjoin(init->hstry_herdog, "\n");
	ft_strdel(&tmp_hstry);
//	tmp_hstry = init->hstry_herdog;
	//init->hstry_herdog = ft_strjoin(init->hstry_herdog, &init->out_put[5]);
	ft_strdel(&tmp_hstry);
	if (ft_strcmp(&init->out_put[5], init->key) == 0 || ((str[0] == 4 &&
					str[1] == '\0' && ft_strcmp(&init->out_put[0],
						"(hr)>") == 0)))
	{
		end_cursor(init);
		ft_printf("\033[%dD", init->s_col);
		return (init->heredoc_str);
	}
	return (NULL);
}

char		*ft_heredoc(char *str,
		t_init *init)
{
	char	*cmd;

	if (!(ft_check_key(init, str)))
		return (NULL);
	else if (str[0] == 10 && ft_strlen(str) == 1)
	{
		if ((cmd = ft_heredoc_help_(str, init)))
			return (cmd);
		if (ft_strcmp(&init->out_put[5], "") != 0)
		{
			//init->hstry_position = NULL;
			cmd = ft_strjoin(&init->out_put[5], "\n");
			init->heredoc_str = ft_strjoin/*_free*/(init->heredoc_str, cmd);
		}
		ft_init_heredoc(init);
	}
	else
		ft_str_line(str, init);
	//ft_update_tmp_hisory(init);
	return (NULL);
}
