/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 20:48:11 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/06 10:39:48 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*get_dollar_var(char *tmp, int *i)
{
	char	*dollar;
	char	br;

	*i = 1;
	br = 0;
	if (tmp[*i] == '{')
	{
		*i = 2;
		br = 1;
	}
	if (tmp[*i] != '?')
	{
		while (ft_isalnum(tmp[*i]) || ft_strchr(":+-_#=?%", tmp[*i]))
			(*i)++;
		dollar = ft_strsub(tmp, 1, !br ? (*i) - 1 : *i);
	}
	else
	{
		dollar = ft_strdup("?");
		(*i)++;
	}
	return (dollar);
}

void		expand(char **s1, int k, int *j, char *dollar)
{
	if (dollar)
	{
		(*s1)[k] = DOLLAR;
		// printf("dollar: %s\n", dollar);
		if (dollar[0] != '(')
		{
			if (!ft_strpos(":+-_#=?%", dollar))
				expand_dollar(dollar, s1, j, 0);
			else
				expand_dollar(dollar, s1, j, 1);
		}
	}
	else
	{
		(*s1)[k] = TILDE;
		// expand_tilde(s1, j);
	}
}

void	search_and_expand(char **s1, char c)
{
	char	*tmp;
	char	*dollar;
	int		i;
	int		j;
	int		k;

	j = 0;
	while ((tmp = ft_strchr((*s1) + j, c)))
	{
		k = ft_strlen(*s1) - ft_strlen(tmp);
		if (c == DOLLAR)
			dollar = get_dollar_var(tmp, &i);
		if ((*s1)[k - 1 > 0 ? k - 1 : 0] != UQ_ESCAPE
		&& (*s1)[k - 1 > 0 ? k - 1 : 0] != Q_ESCAPE)
			c == DOLLAR ? expand(s1, k, &j, dollar) : expand(s1, k, &j, NULL);
		else
			j = c == DOLLAR ? k + i : j + 1;
		if (c == DOLLAR)
			free(dollar);
	}
}

void		update_arg(char *arg, char **tmp, int *k, char type)
{
	char	*s;

	if (!type || type == 1)
	{
		s = get_substring(arg, k, type);
		search_and_expand(&s, DOLLAR);
		if (!type)
			search_and_expand(&s, '~');
		else
			quoted_escape(&s);
	}
	else
	{
		(*k)++;
		s = get_substring(arg, k, 1);
		(*k)++;
	}
	*tmp = ft_fstrjoin(*tmp, s);
}

/*
** - Expand all if argument is not quoted.
** - Expand only environment variables if double quoted.
** - No expansions if argument is single quoted.
*/

void		apply_expansions(char **args)
{
	char	*tmp;
	int		k;

	while (*args)
	{
		quotes_delimiter(args);
		k = 0;
		tmp = ft_strnew(0);
		while ((*args)[k])
		{
			if ((*args)[k] != QUOTE && (*args)[k] != D_QUOTE)
				update_arg(*args, &tmp, &k, 0);
			else if ((*args)[k] != QUOTE)
				update_arg(*args, &tmp, &k, 1);
			else if ((*args)[k])
				update_arg(*args, &tmp, &k, 2);
		}
		free(*args);
		*args = tmp;
		// printf("\narg: %s\n", *args);
		remove_escapes(args, UQ_ESCAPE);
		remove_escapes(args, Q_ESCAPE);
		remove_quotes(args);
		args++;
	}
}
