/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_helper_funcs2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:08:14 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/14 13:35:22 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	isspace(int c)
{
	unsigned char s;

	s = c;
	if (s == ' ' || s == '\t'
		|| s == '\v' || s == '\r' || s == '\f')
		return (1);
	return (0);
}

void		quotes_delimiter(char **tmp)
{
	int		i;
	int		q;
	int		dq;
	int		b_p;

	q = 0;
	dq = 0;
	i = 0;
	b_p = 0;
	while ((*tmp)[i])
	{
		if ((*tmp)[i] == '(' || (*tmp)[i] == '{')
			b_p++;
		else if ((*tmp)[i] == ')' || (*tmp)[i] == '}')
			b_p--;
		if (!b_p)
		{
			if (!q && (*tmp)[i] == '"' &&
			(*tmp)[(i - 1 > 0) ? i - 1 : 0] != Q_ESCAPE
			&& (*tmp)[(i - 1 > 0) ? i - 1 : 0] != UQ_ESCAPE)
			{
				dq = !dq;
				(*tmp)[i] = D_QUOTE;
			}
			else if (!dq && (*tmp)[i] == '\'' &&
			(*tmp)[(i - 1 > 0) ? i - 1 : 0] != Q_ESCAPE &&
			(*tmp)[(i - 1 > 0) ? i - 1 : 0] != UQ_ESCAPE)
			{
				q = !q;
				(*tmp)[i] = QUOTE;
			}
			else if (dq && isspace((*tmp)[i]))
				(*tmp)[i] = BLANK;
		}
		i++;
	}
	// printf("tmp: %s\n", *tmp);
}

void		remove_dq(char **tmp)
{
	char	**tmp2;
	char	**f;

	tmp2 = ft_strsplit(*tmp, D_QUOTE);
	f = tmp2;
	free(*tmp);
	*tmp = ft_strnew(0);
	while (*tmp2)
	{
		*tmp = ft_fstrjoin(*tmp, *tmp2);
		tmp2++;
	}
	free(f);
}

void		remove_q(char **tmp)
{
	char	**tmp2;
	char	**f;

	tmp2 = ft_strsplit(*tmp, QUOTE);
	f = tmp2;
	free(*tmp);
	*tmp = ft_strnew(0);
	while (*tmp2)
	{
		*tmp = ft_fstrjoin(*tmp, *tmp2);
		tmp2++;
	}
	free(f);
}

void		remove_quotes(char **args)
{
	int		i;
	char	*tmp;
	char	s_q;
	char	s_dq;

	i = 0;
	s_dq = 0;
	s_q = 0;
	tmp = ft_strdup(*args);
	remove_dq(&tmp);
	remove_q(&tmp);
	free(*args);
	*args = tmp;
}

void		remove_escapes(char **str, char escape)
{
	char	**tmp;
	int		i;

	tmp = ft_strsplit(*str, escape);
	free(*str);
	*str = ft_strnew(0);
	i = 0;
	while (tmp[i])
	{
		*str = ft_fstrjoin(*str, tmp[i]);
		i++;
	}
	free(tmp);
}
