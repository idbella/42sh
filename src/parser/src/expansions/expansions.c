/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 20:48:11 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/11 14:53:54 by yoyassin         ###   ########.fr       */
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
	if ((*i) == 1)
	{
		while (tmp[*i] && (ft_isalnum(tmp[*i]) || tmp[*i] == '_' || tmp[*i] == '?'))
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
	// }
	// else
	// 	dollar = *i == 1 ? ft_strdup("?") : ft_strdup("{?}");
	return (dollar);
}

void		expand_param(char **s, char type)
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
	param = NULL;
	while ((tmp = ft_strrchr((*s) + j, DOLLAR)))
	{
		k = ft_strlen(*s) - ft_strlen(tmp);
		str[0] = ft_strsub(*s, 0, k);
		if ((*s)[k + 1] == '(')
		{
			param = get_dollar_var(tmp, &i, 0);
			if ((*s)[ft_strlen(param) + k + 1])
				str[1] = ft_strdup((*s) + ft_strlen(param) + k + 1);
			if ((exp = control_subtitution(param, type)))
				str[0] = ft_strjoin(str[0], exp);
		}
		else
		{
			param = get_dollar_var(tmp, &i, 1);
			if ((*s)[ft_strlen(param) + k + 1])
				str[1] = ft_strdup((*s) + ft_strlen(param) + k + 1);
			if (param[0] == '{')
				param = ft_strsub(param, 1, ft_strlen(param) - 2);
			if ((exp = get_param_expan(param)))
				str[0] = ft_strjoin(str[0], exp);
		}
		if (str[0] && !ft_strlen(str[0]))
			str[0][0] = BLANK;
		if (str[1] && !ft_strlen(str[1]))
			str[1][0] = BLANK;
		*s = ft_strjoin(str[0] ? str[0] : ft_strnew(0), str[1] ? str[1] : ft_strnew(0));
	}
}

void		search_and_expand(char **s, char type)
{
	char	*tmp;
	char	*param;
	int		j;
	int		i;
	int		k;
	int		len;
	char	*exp;
	char	*str[2] = {NULL, NULL};

	tmp = NULL;
	j = 0;
	i = 0;
	len = 0;
	while ((tmp = ft_strchr((*s) + j, DOLLAR)))
	{
		k = ft_strlen(*s) - ft_strlen(tmp);
		str[0] = ft_strsub(*s, 0, k);
		str[1] = NULL;
		if ((*s)[k + 1] == '(')
		{
			param = get_dollar_var(tmp, &i, 0);
			if ((*s)[ft_strlen(param) + k + 1])
				str[1] = ft_strdup((*s) + ft_strlen(param) + k + 1);
			if ((exp = control_subtitution(param, type)))
				str[0] = ft_strjoin(str[0], exp);
		}
		else
		{
			param = get_dollar_var(tmp, &i, 1);
			if (ft_strchr(param, DOLLAR))
			{
				len = ft_strlen(param);
				if ((*s)[ft_strlen(param) + k + 1])
					str[1] = ft_strdup((*s) + len + k + 1);
				expand_param(&param, type);
				if (param[0] == '{')
					param = ft_strsub(param, 1, ft_strlen(param) - 2);
			}
			else
			{
				if (param[0] == '{')
					param = ft_strsub(param, 1, ft_strlen(param) - 2);
			}
			if ((exp = get_param_expan(param)))
				str[0] = ft_strjoin(str[0], exp);
		}
		if (str[0] && !ft_strlen(str[0]))
			str[0][0] = BLANK;
		if (str[1] && !ft_strlen(str[1]))
			str[1][0] = BLANK;
		*s = ft_strjoin(str[0] ? str[0] : ft_strnew(0), str[1] ? str[1] : ft_strnew(0));
		str[1] = NULL;
		if ((size_t)j < ft_strlen(*s))
			j += 1;
	}
}

void		update_arg(char *arg, char **tmp, int *k, char type)
{
	char	*s;

	if (!type || type == 1)
	{
		s = get_substring(arg, k, type);
		search_and_expand(&s, type);
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

char		**convert_args(t_arg *h, int size)
{
	char	**new;
	int 	i;
	int		j;

	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (h)
	{
		i = 0;
		while (h->arg[i])
		{
			new[j] = ft_strdup(h->arg[i]);
			i++;
			j++;
		}
		h = h->next;
	}
	new[j] = NULL;
	return (new);
}

char 		**apply_expansions(char **args)
{
	char	*tmp;
	int		k;
	int		size;
	t_arg	*h = NULL;
	t_arg	*c = NULL;
	t_arg	*t = NULL;

	size = 0;
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
		remove_escapes(args, UQ_ESCAPE);
		remove_escapes(args, Q_ESCAPE);
		remove_quotes(args);
		c = malloc(sizeof(t_arg));
		if (ft_strchr(*args, BLANK))
		{
			c->arg = ft_strsplit(*args, BLANK);
			int	j = 0;
			while (c->arg[j])
				j++;
			size += j;
		}
		else
		{
			c->arg = (char **)malloc(sizeof(char *) * 2);
			c->arg[0] = ft_strdup(*args);
			c->arg[1] = NULL;
			size++;
		}
		c->next = NULL;
		if (!h)
			h = c;
		else
			t->next = c;
		t = c;
		args++;
	}
	char **new = NULL;
	new = convert_args(h, size);
	return (new);
}
