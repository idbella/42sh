/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:49:44 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/14 13:34:43 by yoyassin         ###   ########.fr       */
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
	{
		dprintf(2, "WHY THO ??? \n");
		return ((line[i] = IN_RED_OP));
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
	while (line[++i])
	{
		if (!b_p && !q && line[i] == '"' && NEQ_ESCAPE(i))
			dq = !dq;
		else if (!b_p && !dq && line[i] == '\'' && NEQ_ESCAPE(i))
			q = !q;
		else if ((line[i] == '{' || line[i] == '(') && NEQ_ESCAPE(i))
			b_p++;
		else if ((line[i] == '}' || line[i] == ')') && NEQ_ESCAPE(i))
			b_p--;
		if (!q && !dq && NEQ_ESCAPE(i))
		{
			if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1])
			|| line[i + 1] == '{' || line[i + 1] == '(' || line[i + 1] == '_'
			|| line[i + 1] == '?'))
			{
				line[i] = DOLLAR;
				continue ;
			}
			if (!b_p && (dc_operator(line, i) || sc_operator(line, i)))
				continue ;
			else if (!b_p && isspace(line[i]))
				line[i] = BLANK;
		}
		else if (dq && line[(i - 1 > 0) ? i - 1 : 0] != Q_ESCAPE &&
		line[i] == 92)
			line[i] = Q_ESCAPE;
		else if (dq && NEQ_ESCAPE(i) && line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1])
		|| line[i + 1] == '{' || line[i + 1] == '(' || line[i + 1] == '_'
		|| line[i + 1] == '?'))
			line[i] = DOLLAR;
	}
}
