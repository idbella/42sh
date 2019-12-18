/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 20:48:11 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/18 13:05:43 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	- to expand or not to.
*/

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
	// printf("tmp: %s\n", tmp);
	dollar = ft_strsub(tmp, 1, (*i) - 1);
	// dprintf(2, "tmp: %s\ndollar: %s\n\n", tmp, dollar);
	// }
	// else
	// 	dollar = *i == 1 ? ft_strdup("?") : ft_strdup("{?}");
	return (dollar);
}
void		ctl_subst(char *s, char *tmp, char **str, char type);
void		expand_param(char **s, char type)
{
	char	*tmp;
	char	*param;
	int		j;
	int		i;
	int		k;
	char	*str[2] = {NULL, NULL};
	char	*exp;

	printf("*s: %s\n", *s);
	tmp = NULL;
	j = 0;
	i = 0;
	param = NULL;
	while ((tmp = ft_strrchr((*s) + j, DOLLAR)))
	{
		k = ft_strlen(*s) - ft_strlen(tmp);
		if (k > 0)
			str[0] = ft_strsub(*s, 0, k);
		if ((*s)[k + 1] == '(')
			ctl_subst((*s) + k, tmp, &str[1], type);
		else
		{
			param = get_dollar_var(tmp, &i, 1);
			if ((*s)[ft_strlen(param) + k + 1])
				str[1] = ft_strdup((*s) + ft_strlen(param) + k + 1);
			if (param[0] == '{')
				param = ft_strsub(param, 1, ft_strlen(param) - 2);
			if ((exp = get_param_expan(param)))
				str[0] = str[0] ? ft_strjoin(str[0], exp) : ft_strdup(exp);
		}
		if (str[0] && !ft_strlen(str[0]))
			str[0][0] = BLANK;
		if (str[1] && !ft_strlen(str[1]))
			str[1][0] = BLANK;
		*s = ft_strjoin(str[0] ? str[0] : ft_strnew(0), str[1] ? str[1] : ft_strnew(0));
		str[0] = NULL;
		str[1] = NULL;
	}
}

void		ctl_subst(char *s, char *tmp, char **str, char type)
{
	char	*param;
	char	*exp;
	int		i;

	i = 0;
	param = NULL;
	exp = NULL;
	param = get_dollar_var(tmp, &i, 0);
	if (s[ft_strlen(param) + 1])
		*str = ft_strdup(s + ft_strlen(param) + 1);
	if ((exp = control_subtitution(param, type)) && ft_strlen(exp))
	{
		if (*str)
			*str = ft_fstrjoin(exp, *str);
		else
		{
			*str = ft_strdup(exp);
			free(exp);
		}
	}
	free(param);
}

void		search_and_expand(char **s, char type)
{
	char	*tmp;
	char	*param;
	int		j;
	int		i;
	int		k;
	int		len;
	char	*exp = NULL;
	char	*str[2] = {NULL, NULL};
	char	dq;
	int		pos;

	tmp = NULL;
	j = 0;
	i = 0;
	len = 0;
	dq = 0;
	while ((tmp = ft_strchr((*s) + j, DOLLAR)))
	{
		k = ft_strlen(*s) - ft_strlen(tmp);
		str[0] = NULL;
		str[1] = NULL;
		if (k > 0)
			str[0] = ft_strsub(*s, 0, k);
		if ((*s)[k + 1] == '(')
		{
			pos = 0;
			while (pos < k)
			{
				if ((*s)[pos] == D_QUOTE)
					dq = !dq;
				pos++;
			}
			ctl_subst((*s) + k, tmp, &str[1], dq ? 1 : 0);
		}
		else
		{
			param = get_dollar_var(tmp, &i, 1);
			len = ft_strlen(param);
			if ((*s)[ft_strlen(param) + k + 1])
				str[1] = ft_strdup((*s) + len + k + 1);
			if (ft_strchr(param, DOLLAR))
			{
				expand_param(&param, type);
				if (param[0] == '{')
					param = ft_strsub(param, 1, ft_strlen(param) - 2);
			}
			else
			{
				if (param[0] == '{')
					param = ft_strsub(param, 1, ft_strlen(param) - 2);
			}
			if ((exp = get_param_expan(param)) && ft_strlen(exp))
				str[0] = str[0] ? ft_strjoin(str[0], exp) : ft_strdup(exp);
		}
		if (str[0] && !ft_strlen(str[0]))
			str[0][0] = BLANK;
		if (str[1] && !ft_strlen(str[1]))
			str[1][0] = BLANK;
		// free(*s);
		*s = ft_strjoin(str[0] ? str[0] : ft_strnew(0),
		str[1] ? str[1] : ft_strnew(0));
		if ((size_t)j < ft_strlen(*s))
			j += 1;
	}
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
			if (!ft_strlen(h->arg[i]))
			{
				i++;
				continue ;
			}
			new[j] = ft_strdup(h->arg[i]);
			i++;
			j++;
		}
		h = h->next;
	}
	new[j] = NULL;
	return (new);
}

int			expand(char **args, t_arg *c)
{
	int		k;
	char	*tmp;
	int		size;

	k = 0;
	size = 0;
	tmp = ft_strdup(*args);
	search_and_expand(&tmp, 0);
	quoted_escape(&tmp);
	expand_tilde(&tmp);
	free(*args);
	*args = tmp;
	remove_escapes(args, UQ_ESCAPE);
	remove_escapes(args, Q_ESCAPE);
	remove_quotes(args);
	if (ft_strchr(*args, BLANK))
	{
		c->arg = ft_strsplit(*args, BLANK);
		int	j = 0;
		while (c->arg[j])
		{
			if (ft_strlen(c->arg[j]))
				size++;
			j++;
		}
	}
	else
	{
		c->arg = (char **)malloc(sizeof(char *) * 2);
		c->arg[0] = ft_strdup(*args);
		c->arg[1] = NULL;
		if (ft_strlen(*args))
			size++;
	}
	return (size);
}

char		**get_assignments(char ***args)
{
	int		pos;
	char	flag;
	int		size = 0;
	t_arg	*h = NULL;
	t_arg	*c = NULL;
	t_arg	*t = NULL;

	pos = 0;
	while (**args)
	{
		quotes_delimiter(*args);
		flag = 1;
		if ((pos = ft_strpos(**args, "=")) != -1)
		{
			flag = 0;
			while (pos >= 0 && (**args)[pos])
			{
				if ((**args)[pos] != QUOTE && (**args)[pos] != D_QUOTE
				&& (**args)[pos] != Q_ESCAPE && (**args)[pos] != UQ_ESCAPE)
					pos--;
				else
				{
					flag = 1;
					break ;
				}
			}
			if (!flag)
			{
				c = malloc(sizeof(t_arg));
				c->next = NULL;
				size += expand(*args, c);
				if (!h)
					h = c;
				else
					t->next = c;
				t = c;
			}
		}
		if (flag)
			break ;
		(*args)++;
	}
	return (convert_args(h, size));
}

void		apply_expansions(t_process *process)
{
	int		size;
	t_arg	*h = NULL;
	t_arg	*c = NULL;
	t_arg	*t = NULL;
	char	**args;

	size = 0;
	args = process->arg;
	process->ass = get_assignments(&args);
	while (*args)
	{
		quotes_delimiter(args);
		c = malloc(sizeof(t_arg));
		c->next = NULL;
		size += expand(args, c);
		if (!h)
			h = c;
		else
			t->next = c;
		t = c;
		args++;
	}
	process->arg = convert_args(h, size);
}
