/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 20:48:11 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/08 19:06:44 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*get_dollar_var(char *tmp, int *i, char op)
{
	char	*dollar;
	char	open;

	*i = 1;
	if (tmp[*i] == '{' || tmp[*i] == '(')
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
				if (op)
				{
					if (tmp[*i] == '{')
						open += 1;
					else if (tmp[*i] == '}')
						open -= 1;
				}
				else
				{
					if (tmp[*i] == '(')
						open += 1;
					else if (tmp[*i] == ')')
						open -= 1;
				}
				(*i)++;
			}
		}
		dollar = ft_strsub(tmp, 1, (*i) - 1);
	}
	else
		dollar = *i == 1 ? ft_strdup("?") : ft_strdup("{?}");
	return (dollar);
}

// void		expand(char **s1, int k, int *j, char *dollar)
// {
// 	if (dollar)
// 	{
// 		(void)k;
// 		if (dollar[0] != '(')
// 			// expand_dollar(dollar, s1, j);
// 		else
// 		{
// 			// control_subtitution(dollar, s1, j);
// 			// (*j)++;
// 		}
// 	}
// }

void		expand_param(char **s)
{
	char	*tmp;
	char	*param;
	int		j;
	int		i;
	int		k;
	char	*str[2] = {NULL, NULL};
	char	*exp;

	tmp = NULL;
	j = 0;
	i = 0;
	while ((tmp = ft_strrchr((*s) + j, DOLLAR)))
	{
		k = ft_strlen(*s) - ft_strlen(tmp);
		if ((*s)[k + 1] == '(')
		{
			param = get_dollar_var(tmp, &i, 0);
			control_subtitution(param, s, &j);
		}
		else
		{
			param = get_dollar_var(tmp, &i, 1);
			str[0] = ft_strsub(*s, 0, k);
			if ((*s)[ft_strlen(param) + k + 1])
				str[1] = ft_strdup((*s) + ft_strlen(param) + k + 1);
			param = ft_strsub(param, 1, ft_strlen(param) - 2);
			if ((exp = get_param_expan(param)))
				str[0] = ft_strjoin(str[0], exp);
			*s = ft_strjoin(str[0] ? str[0] : ft_strnew(0), str[1] ? str[1] : ft_strnew(0));
		}
	}
}

void		search_and_expand(char **s)
{
	char	*tmp;
	char	*param;
	int		j;
	int		i;
	int		k;
	int		len;

	tmp = NULL;
	j = 0;
	i = 0;
	len = 0;
	while ((tmp = ft_strchr((*s) + j, DOLLAR)))
	{
		k = ft_strlen(*s) - ft_strlen(tmp);
		if ((*s)[k + 1] == '(')
		{
			param = get_dollar_var(tmp, &i, 0);
			control_subtitution(param, s, &j);
		}
		else
		{
			param = get_dollar_var(tmp, &i, 1);
			if (ft_strchr(param, DOLLAR))
			{
				len = ft_strlen(param);
				expand_param(&param);
				expand_dollar(param, s, &j, len);
			}
			else
				expand_dollar(param, s, &j, -1);
		}
		j += 1;
	}
}

void		update_arg(char *arg, char **tmp, int *k, char type)
{
	char	*s;

	if (!type || type == 1)
	{
		s = get_substring(arg, k, type);
		search_and_expand(&s);
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
