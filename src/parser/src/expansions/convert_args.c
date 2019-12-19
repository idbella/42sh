/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 11:43:16 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/19 15:28:23 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**ft_newarray(int size)
{
	char	**new;
	int		i;

	new = NULL;
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < size)
		new[i++] = NULL;
	return (new);
}

char		**convert_args(t_arg *h, int size)
{
	char	**new;
	int		i;
	int		j;
	t_arg	*next;

	new = ft_newarray(size);
	j = 0;
	while (h)
	{
		next = h->next;
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
		free(h);
		h = next;
	}
	new[j] = NULL;
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
		c->arg = (char **)malloc(sizeof(char *) * 2);
		c->arg[0] = ft_strdup(*args);
		c->arg[1] = NULL;
		if (ft_strlen(*args))
			(*size)++;
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
