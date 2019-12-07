/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 20:48:11 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/07 17:17:20 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*get_dollar_var(char *tmp, int *i)
{
	char	*dollar;
	char	open;

	*i = 1;
	if (tmp[*i] == '{')
		*i = 2;
	if (tmp[*i] != '?')
	{
		if ((*i) == 1)
		{
			while (tmp[*i] && (ft_isalnum(tmp[*i]) || tmp[*i] == '_'))
				(*i)++;
		}
		else
		{
			open = 1;
			while (tmp[*i] && open)
			{
				if (tmp[*i] == '{')
					open += 1;
				else if (tmp[*i] == '}')
					open -= 1;
				(*i)++;
			}
		}
		dollar = ft_strsub(tmp, 1, (*i) - 1);
	}
	else
		dollar = *i == 1 ? ft_strdup("?") : ft_strdup("{?}");
	return (dollar);
}

// char		*parse_dollar(char *dollar)
// {
// 	char	*new;

// 	new = NULL;
// 	while (dollar)
// }

void		expand(char **s1, int k, int *j, char *dollar)
{
	if (dollar)
	{
		(*s1)[k] = DOLLAR;
		if (dollar[0] != '(')
		{
			// dollar = parse_dollar(dollar);
			if (!ft_strpos(":+-_#=?%", dollar))
				expand_dollar(dollar, s1, j, 0);
			else
				expand_dollar(dollar, s1, j, 1);
		}
		else
		{
			control_subtitution(dollar, s1, j);
			(*j)++;
		}
	}
}

void	search_and_expand(char **s1, char c)
{
	char	*tmp;
	char	*param;
	int		i;
	int		j;
	int		k;

	j = 0;
	while ((tmp = ft_strchr((*s1) + j, c)))
	{
		k = ft_strlen(*s1) - ft_strlen(tmp);
		if (c == DOLLAR)
			param = get_dollar_var(tmp, &i);
		// printf("dollar: %s\n", param);
		if ((*s1)[k - 1 > 0 ? k - 1 : 0] != UQ_ESCAPE
		&& (*s1)[k - 1 > 0 ? k - 1 : 0] != Q_ESCAPE)
			expand(s1, k, &j, param);
		else
			j = k + i;
		if (c == DOLLAR)
			free(param);
	}
}

void		update_arg(char *arg, char **tmp, int *k, char type)
{
	char	*s;

	if (!type || type == 1)
	{
		s = get_substring(arg, k, type);
		search_and_expand(&s, DOLLAR);
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
		expand_tilde(&tmp);
		free(*args);
		*args = tmp;
		// printf("\narg: %s\n", *args);
		remove_escapes(args, UQ_ESCAPE);
		remove_escapes(args, Q_ESCAPE);
		remove_quotes(args);
		args++;
	}
}
