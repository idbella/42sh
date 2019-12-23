/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 11:43:16 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/23 15:26:20 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**convert_args(t_arg *h, int size)
{
	char	**new;
	int		i;
	int		j;

	new = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	j = 0;
	while (h)
	{
		i = -1;
		while (h->arg[++i])
		{
			if (!ft_strlen(h->arg[i]))
			{
				free(h->arg[i]);
				continue ;
			}
			new[j++] = h->arg[i];
		}
		h = h->next;
	}
	return (new);
}

void		store_args(t_arg *c, char **args, int *size)
{
	int	j;

	j = 0;
	if (ft_strchr(*args, BLANK))
	{
		c->arg = ft_strsplit(*args, BLANK);
		j = 0;
		while (c->arg[j])
		{
			if (ft_strlen(c->arg[j]))
				(*size)++;
			j++;
		}
	}
	else
	{
		if (ft_strlen(*args) &&
		(c->arg = (char **)ft_memalloc(sizeof(char *) * 2)))
		{
			c->arg[0] = ft_strdup(*args);
			c->arg[1] = NULL;
			(*size)++;
		}
	}
}

void		valid_assignment(char *args, char *flag, int pos)
{
	*flag = 0;
	pos--;
	while (pos >= 0 && args[pos])
	{
		if (args[pos] != QUOTE && args[pos] != D_QUOTE
		&& args[pos] != Q_ESCAPE && args[pos] != UQ_ESCAPE
		&& (args[pos] == '_' || ft_isalnum(args[pos])))
			pos--;
		else
		{
			*flag = 1;
			break ;
		}
	}
	if (!*flag && args[pos + 1])
	{
		if (ft_isdigit(args[pos + 1]))
			*flag = 1;
	}
}
