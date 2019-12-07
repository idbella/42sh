/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_helper_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:12:10 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/07 17:22:48 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	expand_tilde(char **args)
{
	int		j;
	char	*tilde;
	char	*expansion;
	int		len;
	char	*s;

	tilde = NULL;
	len = 0;
	if ((j = ft_strpos((*args), "~")) != -1)
	{
		if (j)
			return ;
		else if ((*args)[1] && !is_word((*args) + 1))
			if ((*args)[1] != '/')
				return ;
		while ((*args)[j] && (*args)[j] != '/')
			j++;
		tilde = ft_strsub(*args, 0, j);
		expansion = ft_strdup(tild_expan(tilde));
		len = ft_strlen(*args);
		if (expansion)
		{
			s = ft_strsub(*args, j, !(len - j) ? 1 : (len - j));
			*args = ft_fstrjoin(expansion, s);
		}
	}
}

void	expand_dollar(char *dollar, char **args, int *j, char op)
{
	char	*s1;
	char	*s2;
	char	*tmp2;
	int		pos;
	char	ds[2];
	char	*expansion;

	expansion = NULL;
	ds[0] = DOLLAR;
	ds[1] = 0;
	pos = ft_strpos(*args, ds);
	s1 = ft_strsub(*args, 0, pos);
	s2 = ft_strsub(*args, pos + ft_strlen(dollar) + 1,
	ft_strlen(*args) - (ft_strlen(dollar) + ft_strlen(s1)) - 1);
	dollar = dollar[0] == '{' ? ft_strsub(dollar, 1, ft_strlen(dollar) - 2) : dollar;
	expansion = !op ? ft_getenv(dollar) : get_param_expan(dollar);
	if ((*args)[pos + 1] == '?')
		s1 = ft_fstrjoin(s1, ft_itoa(ft_get_last_rvalue(), 10));
	else if (expansion)
	{
		tmp2 = s1;
		s1 = ft_strjoin(s1, expansion);
		free(tmp2);
	}
	*j = ft_strlen(s1);
	tmp2 = *args;
	*args = ft_fstrjoin(s1, s2);
	free(tmp2);
}

void	quoted_escape(char **arg)
{
	char	*s[4];
	char	*esc;
	int		pos;
	int		j;

	j = 0;
	s[1] = NULL;
	s[2] = ft_strnew(0);
	while ((esc = ft_strchr((*arg) + j, Q_ESCAPE)))
	{
		pos = ft_strlen(*arg) - ft_strlen(esc);
		s[1] = ft_strsub(*arg, j, pos - j);
		s[1] = get_esc_char(s[1], (*arg)[pos + 1]);
		s[2] = ft_fstrjoin(s[2], s[1]);
		j = pos + 2;
	}
	s[3] = ft_strdup((*arg) + j);
	s[1] = ft_fstrjoin(s[2], s[3]);
	free(*arg);
	*arg = s[1];
}

int		ft_strind(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_substring(char *str, int *k, char type)
{
	int	start;
	int	len;

	start = *k;
	len = 0;
	if (!type)
	{
		while (str[*k] && str[*k] != QUOTE && str[*k] != D_QUOTE)
		{
			(*k)++;
			len++;
		}
	}
	else
	{
		while (str[*k] && str[*k] != QUOTE)
		{
			(*k)++;
			len++;
		}
	}
	return (ft_strsub(str, start, len));
}
