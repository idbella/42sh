/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:49:44 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/19 19:15:25 by yoyassin         ###   ########.fr       */
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

int			dc_operator(char *line, int i)
{
	if (line[i] == '&' && line[i + 1] == '&')
	{
		line[i] = AND;
		return ((line[i + 1] = AND));
	}
	else if (line[i] == '|' && line[i + 1] == '|')
	{
		line[i] = OR;
		return ((line[i + 1] = OR));
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		line[i] = APP_OUT_RED_OP;
		return ((line[i + 1] = APP_OUT_RED_OP));
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		line[i] = HEREDOC_OP;
		return ((line[i + 1] = HEREDOC_OP));
	}
	return (0);
}

int			sc_operator(char *line, int i)
{
	if (line[i] == ';')
		return ((line[i] = SEMI_COL));
	else if (line[i] == 92 && line[(i - 1 > 0) ? i - 1 : 0] != UQ_ESCAPE)
		return ((line[i] = UQ_ESCAPE));
	else if (line[i] == '|' && line[i + 1] != '|')
		return ((line[i] = PIPE));
	else if (line[i] == '>' && line[i + 1] != '>')
		return ((line[i] = OUT_RED_OP));
	else if (line[i] == '<' && line[i + 1] != '<')
		return ((line[i] = IN_RED_OP));
	return (0);
}

int			is_dollar(char *line, int i, char dq)
{
	if (!dq)
	{
		if (L[i] == '$' && L[i + 1] && (ft_isalnum(L[i + 1]) || L[i + 1] == '{'
			|| L[i + 1] == '(' || L[i + 1] == '_' || L[i + 1] == '?'))
			return ((L[i] = DOLLAR));
	}
	else
	{
		if (NEQ_ESCAPE(i) && L[i] == '$' && L[i + 1] && (ft_isalnum(L[i + 1])
		|| L[i + 1] == '{' || L[i + 1] == '(' || L[i + 1] == '_'
		|| L[i + 1] == '?'))
			return (1);
	}
	return (0);
}

void		operator_check(char *line, int i, char dq, char b_p)
{
	if (IS_DOLLAR(dq))
		return ;
	if (!b_p && (dc_operator(L, i) || sc_operator(L, i)))
		return ;
	else if (!b_p && isspace(L[i]))
		L[i] = BLANK;
	return ;
}

int			quote(char *line, int i, char *dq, char *q)
{
	if (!*q && L[i] == '"' && NEQ_ESCAPE(i))
	{
		*dq = !*dq;
		return (1);
	}
	else if (!*dq && L[i] == '\'' && NEQ_ESCAPE(i))
	{
		*q = !*q;
		return (1);
	}
	return (0);
}

void		mark_operators(char *line)
{
	int		i;
	char	q;
	char	dq;
	int		b_p;

	q = 0;
	dq = 0;
	i = -1;
	b_p = 0;
	while (L[++i])
	{
		if (quote(L, i, &dq, &q))
			continue ;
		else if ((L[i] == '{' || L[i] == '(') && NEQ_ESCAPE(i))
			b_p++;
		else if ((L[i] == '}' || L[i] == ')') && NEQ_ESCAPE(i))
			b_p--;
		if (!q && !dq && NEQ_ESCAPE(i))
			operator_check(L, i, dq, b_p);
		else if (dq && L[(i - 1 > 0) ? i - 1 : 0] != Q_ESCAPE && L[i] == 92)
			L[i] = Q_ESCAPE;
		else if (IS_DOLLAR(dq))
			L[i] = DOLLAR;
	}
}
