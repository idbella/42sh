/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_helper_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:12:10 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/02 16:30:53 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// void	expand_tilde(char **args, int *j)
// {
// 	t_env	*curr;
// 	char	*s1;
// 	char	*s2;
// 	char	*tmp;
// 	char	tilde[2];

// 	tilde[0] = TILDE;
// 	tilde[1] = 0;
// 	s1 = ft_strsub(*args, 0, ft_strpos(*args, tilde));
// 	s2 = ft_strsub(*args, ft_strpos(*args, tilde) + 1,
// 	ft_strlen(*args) - ft_strlen(s1) - 1);
// 	if ((curr = ft_getenv("HOME", get_shell_cfg(0)->env)))
// 	{
// 		tmp = s1;
// 		s1 = ft_strjoin(s1, curr->value);
// 		free(tmp);
// 	}
// 	*j = ft_strlen(s1);
// 	tmp = *args;
// 	*args = ft_fstrjoin(s1, s2);
// 	free(tmp);
// }

void	expand_dollar(char *dollar, char **args, int *j)
{
	char	*s1;
	char	*s2;
	char	*tmp2;
	int		pos;
	char	ds[2];

	ds[0] = DOLLAR;
	ds[1] = 0;
	pos = ft_strpos(*args, ds);
	s1 = ft_strsub(*args, 0, pos);
	s2 = ft_strsub(*args, pos + ft_strlen(dollar) + 1,
	ft_strlen(*args) - (ft_strlen(dollar) + ft_strlen(s1)) - 1);
	dollar = dollar[0] == '{' ? ft_strsub(dollar, 1, ft_strlen(dollar) - 2) : dollar;
	if ((*args)[pos + 1] == '?')
		s1 = ft_fstrjoin(s1, ft_itoa(ft_get_last_rvalue(), 10));
	else if (ft_getenv(dollar))
	{
		tmp2 = s1;
		s1 = ft_strjoin(s1, ft_getenv(dollar));
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
