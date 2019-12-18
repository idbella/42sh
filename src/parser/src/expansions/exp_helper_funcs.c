/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_helper_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:12:10 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/18 19:27:12 by yoyassin         ###   ########.fr       */
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
