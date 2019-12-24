/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:31:52 by oherba            #+#    #+#             */
/*   Updated: 2019/12/24 16:33:25 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_free_auto_lst(t_auto **lst)
{
	if ((*lst))
	{
		if ((*lst)->next)
			ft_free_auto_lst(&(*lst)->next);
		ft_strdel(&((*lst)->str));
		free(*lst);
		*lst = NULL;
	}
}

int	ft_is_var(char *to_complete)
{
	int i;
	int n;
	char *tmp;

	i = 0;
	n = 0;
	tmp = ft_strdup(to_complete);
	mark_operators(tmp);
	mark_bg_op(tmp);
	if (ft_strlen(to_complete) == 1 && to_complete[0] == '$')
	{
		free(tmp);
		return (1);
	}
	while (tmp[i])
	{
		if (tmp[i] == DOLLAR)
			n++;
		i++;
	}
	ft_strdel(&tmp);
	return (n);
}

void	ft_autocomplete_42(t_init *init)
{
	char *line;

	init->completion_lst = NULL;
	int len = ft_strlen(init->promt);
	line = &(init->out_put[len]);
	init->to_complete = ft_take_to_complte_42(init);
	ft_get_completion_from_x(init, line);
	ft_print_completion_42(init);
	ft_strdel(&init->to_complete);
	ft_free_auto_lst(&(init->completion_lst));
	init->completion_lst = NULL;
}
