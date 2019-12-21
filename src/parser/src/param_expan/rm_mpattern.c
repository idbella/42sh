/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_mpattern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <mmostafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 18:59:34 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/21 10:52:39 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

typedef struct s_mtools
{
	int		i_src;
	int		globing;
	int		i_preffix;
	int		i_suffix;
}				t_mtools;

int		find_preffix(char *src, char *preffix, char preffix_size)
{
	t_mtools	tools;

	tools.i_src = 0;
	tools.i_preffix = 0;
	while (src[tools.i_src] && preffix[tools.i_preffix])
	{
		if (preffix[tools.i_preffix] == '*')
		{
			if ((tools.i_preffix - 1 >= 0 && preffix[tools.i_preffix - 1] != '\\') ||
				tools.i_preffix == 0)
			{
				if (preffix[tools.i_preffix + 1])
				{
					tools.i_preffix++;
					if (preffix_size == 'B')
					{
						tools.globing = ft_strlen(src);
						while (src[tools.globing] != preffix[tools.i_preffix] && tools.globing)
							tools.globing--;
						tools.i_src = tools.globing;
					}
					else
						while (src[tools.i_src] != preffix[tools.i_preffix] && src[tools.i_src])
							tools.i_src++;
				}
				else if (preffix[tools.i_preffix - 1])
				{
					if (preffix_size == 'B')
						return (ft_strlen(src));
					return (tools.i_src);
				}
			}
			else
				tools.i_preffix += 1;
		}
		if (src[tools.i_src] != preffix[tools.i_preffix] || !preffix[tools.i_preffix])
			break;
		tools.i_src++;
		tools.i_preffix++;
	}
	if (preffix[tools.i_preffix])
	{
		return (-1);
	}
	return (tools.i_src);

}

int		find_suffix(char *src, char *suffix, char suffix_size)
{
	t_mtools	tools;

	tools.i_src = ft_strlen(src);
	tools.i_suffix = ft_strlen(suffix);
	while (tools.i_src >= 0 && tools.i_suffix >= 0)
	{
		if (suffix[tools.i_suffix] == '*')
		{
			if ((tools.i_suffix - 1 >= 0 && suffix[tools.i_suffix - 1] != '\\') ||
				tools.i_suffix == 0)
			{
				if (suffix[tools.i_suffix - 1] && (tools.i_suffix - 1) >= 0)
				{
					tools.i_suffix--;
					if (suffix_size == 'S')
					{
						tools.globing = 0;
						while (src[tools.globing] != suffix[tools.i_suffix] && src[tools.globing])
							tools.globing++;
						if (!tools.globing)
							return (0);
						tools.i_src = tools.globing;
					}
					else
						while (src[tools.i_src] != suffix[tools.i_suffix] && tools.i_src)
							tools.i_src--;
				}
				else if (suffix[tools.i_suffix + 1])
				{
					if (suffix_size == 'S')
						return (0);
					return (tools.i_src + 1);
				}
			}
			else
				tools.i_suffix -= 1;
		}
		if (src[tools.i_src] != suffix[tools.i_suffix] || !tools.i_suffix)
			break;
		tools.i_src--;
		tools.i_suffix--;
	}
	if (tools.i_suffix >= 0 && src[tools.i_src] != suffix[tools.i_suffix])
		return (-1);
	return (tools.i_src);
}

char	*rm_suffix(t_param_expan_st *p_w)
{
	int		i_src;
	char	*value;

	value = ft_getvlaue_bykey(p_w->param, INTERN);
	if (p_w->operation_type == 's')
	{
		i_src = find_suffix(value, p_w->word, 's');
		return (ft_strsub(value, 0, i_src));
	}
	if ((i_src = find_suffix(value, p_w->word, 'S')) < 0)
		return (value);
	return (ft_strsub(value, 0, i_src));
}

char	*rm_preffix(t_param_expan_st *p_w)
{
	int		i_src;
	char	*value;

	value = ft_getvlaue_bykey(p_w->param, INTERN);
	if (p_w->operation_type == 'b')
	{
		i_src = find_preffix(value, p_w->word, 'b');
		return (ft_strsub(value, i_src, ft_strlen(value) - i_src));
	}
	if ((i_src = find_preffix(value, p_w->word, 'B')) < 0)
		return (value);
	return (ft_strsub(value, i_src, ft_strlen(value) - i_src));
}
char	*rm_ffixers(t_param_expan_st *param_word)
{
	if (param_word->operation_type == 's' ||
		param_word->operation_type == 'S')
		return (rm_suffix(param_word));
	if (param_word->operation_type == 'B' ||
		param_word->operation_type == 'b')
		return (rm_preffix(param_word));
	return (ft_itoa((int)ft_strlen(ft_getvlaue_bykey(param_word->param,
			INTERN)), 10));
}
