/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_mpattern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <mmostafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 18:59:34 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/04 13:35:12 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		find_preffix(char *src, char *preffix, char preffix_size)
{
	int		i_src;
	int		init;
	int		globing;
	int		i_preffix;

	i_src = 0;
	i_preffix = 0;
	init = 0;
	while (src[i_src] && preffix[i_preffix])
	{
		if (preffix[i_preffix] == '*')
		{
			if ((i_preffix - 1 >= 0 && preffix[i_preffix - 1] != '\\') ||
				i_preffix == 0)
			{
				i_preffix++;
				if (preffix_size == 'B')
				{
					globing = ft_strlen(src);
					while (src[globing] != preffix[i_preffix])
						globing--;
					i_src = globing;
				}
				else
				{
					while (src[i_src] != preffix[i_preffix] && preffix[i_src])
						i_src++;
				}
			}
			else
				i_preffix -= 2;
		}
		if (src[i_src] != preffix[i_preffix])
			break;
		i_src++;
		i_preffix++;
	}
	if (preffix[i_preffix])
		return (-1);
	return (i_src);

}

int		find_suffix(char *src, char *suffix, char suffix_size)
{
	int		i_src;
	int		init;
	int		globing;
	int		i_suffix;

	i_src = ft_strlen(src);
	i_suffix = ft_strlen(src);
	init = 0;
	while (i_src && i_suffix)
	{
		if (suffix[i_suffix] == '*')
		{
			if ((i_suffix - 1 >= 0 && suffix[i_suffix - 1] != '\\') ||
				i_suffix == 0)
			{
				i_suffix--;
				if (suffix_size == 'S')
				{
					globing = 0;
					while (src[globing] != suffix[i_suffix])
						globing++;
					i_src = globing;
				}
				else
				{
					while (src[i_src] != suffix[i_suffix] && i_src)
						i_src--;
				}
			}
			else
				i_suffix -= 2;
		}
		if (src[i_src] != suffix[i_suffix])
			break;
	}
	if (i_suffix)
		return (-1);
	return (i_src);
}

char	*rm_suffix(t_param_expan_st *p_w)
{
	int		i_src;

	if (p_w->operation_type == 's')
	{
		i_src = find_suffix(p_w->param, p_w->word, 's');
		return (ft_strsub(p_w->param, i_src, ft_strlen(p_w->param) - i_src));
	}
	i_src = find_suffix(p_w->param, p_w->word, 'S');
	return (ft_strsub(p_w->param, i_src, ft_strlen(p_w->param) - i_src));
}

char	*rm_preffix(t_param_expan_st *p_w)
{
	int		i_src;

	if (p_w->operation_type == 'b')
	{
		i_src = find_preffix(p_w->param, p_w->word, 'b');
		return (ft_strsub(p_w->param, 0, i_src));
	}
	i_src = find_suffix(p_w->param, p_w->word, 'B');
	return (ft_strsub(p_w->param, 0, i_src));
}
char	*rm_ffixers(t_param_expan_st *param_word)
{
	if (param_word->operation_type == 's' || param_word->operation_type == 'S')
		return (rm_suffix(param_word));
	if (param_word->operation_type == 'B' || param_word->operation_type == 'b')
		return (rm_preffix(param_word));
	if (param_word->operation_type == 'l')
	{
		return (ft_itoa((int)ft_strlen(ft_getvlaue_bykey(param_word->param, INTERN)), 10));

	}
	return (NULL);
}