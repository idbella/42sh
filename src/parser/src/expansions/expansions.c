/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 20:48:11 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/18 20:14:50 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	search_and_expand(&tmp);
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
