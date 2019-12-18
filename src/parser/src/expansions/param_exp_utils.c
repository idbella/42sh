/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 20:14:38 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/18 20:28:15 by yoyassin         ###   ########.fr       */
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
	return (dollar);
}

int			is_quoted(char *s, int len)
{
	int		i;
	char	dq;

	i = 0;
	while (i < len)
	{
		if (s[i] == D_QUOTE)
			dq = !dq;
		i++;
	}
	return (dq);
}

void		param_subst(char *s, char *tmp, char **str)
{
	char	*param;
	char	*exp;
	int		len;
	int		i;

	param = get_dollar_var(tmp, &i, 1);
	len = ft_strlen(param);
	if (s[len + 1])
		*str = ft_strdup(s + len + 1);
	if (ft_strchr(param, DOLLAR))
	{
		expand_param(&param);
		if (param[0] == '{')
			param = ft_fstrsub(param, 1, ft_strlen(param) - 2);
	}
	else
	{
		if (param[0] == '{')
			param = ft_fstrsub(param, 1, ft_strlen(param) - 2);
	}
	if ((exp = get_param_expan(param)) && ft_strlen(exp))
	{
		if (*str)
			*str = ft_fstrjoin(exp, *str);
		else
		{
			*str = ft_strdup(exp);
			free(exp);
		}
	}
}

void		get_expansion(char *s, char *tmp, char **str)
{
	char	*param;
	char	*exp;
	int		i;
	int		len;

	param = get_dollar_var(tmp, &i, 1);
	len = ft_strlen(param);
	if (s[len + 1])
		*str = ft_strdup(s + len + 1);
	if (param[0] == '{')
		param = ft_fstrsub(param, 1, len - 2);
	if ((exp = get_param_expan(param)))
	{
		if (*str)
			*str = ft_fstrjoin(exp, *str);
		else
		{
			*str = ft_strdup(exp);
			free(exp);
		}
	}
}

void		expand_param(char **s)
{
	char	*tmp;
	int		k;
	char	*str[2] = {NULL, NULL};

	tmp = NULL;
	while ((tmp = ft_strrchr((*s), DOLLAR)))
	{
		k = ft_strlen(*s) - ft_strlen(tmp);
		if (k > 0)
			str[0] = ft_strsub(*s, 0, k);
		if ((*s)[k + 1] == '(')
			ctl_subst((*s) + k, tmp, &str[1], is_quoted(*s, k));
		else
			get_expansion((*s) + k, tmp, &str[1]);
		if (str[0] && !ft_strlen(str[0]))
			str[0][0] = BLANK;
		if (str[1] && !ft_strlen(str[1]))
			str[1][0] = BLANK;
		free(*s);
		*s = ft_fstrjoin(str[0] ? str[0] :
		ft_strnew(0), str[1] ? str[1] : ft_strnew(0));
		str[0] = NULL;
		str[1] = NULL;
	}
}

void		search_and_expand(char **s)
{
	char	*tmp;
	int		j;
	int		i;
	int		k;
	int		len;
	char	*str[2] = {NULL, NULL};

	tmp = NULL;
	j = 0;
	i = 0;
	len = 0;
	while ((tmp = ft_strchr((*s) + j, DOLLAR)))
	{
		k = ft_strlen(*s) - ft_strlen(tmp);
		str[0] = NULL;
		str[1] = NULL;
		if (k > 0)
			str[0] = ft_strsub(*s, 0, k);
		if ((*s)[k + 1] == '(')
			ctl_subst((*s) + k, tmp, &str[1], is_quoted(*s, k));
		else
			param_subst((*s) + k, tmp, &str[1]);
		if (str[0] && !ft_strlen(str[0]))
			str[0][0] = BLANK;
		if (str[1] && !ft_strlen(str[1]))
			str[1][0] = BLANK;
		free(*s);
		*s = ft_fstrjoin(str[0] ? str[0] : ft_strnew(0),
		str[1] ? str[1] : ft_strnew(0));
		if ((size_t)j < ft_strlen(*s))
			j += 1;
	}
}
