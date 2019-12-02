// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_history.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/11/23 01:04:18 by oherba            #+#    #+#             */
// /*   Updated: 2019/11/23 01:24:32 by oherba           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "readline.h"

// void		ft_update_tmp_hisory(t_init *init)
// {
// 	ft_strdel(&init->hstry_tmp);
// 	init->hstry_tmp = ft_strdup(init->out_put);
// }



// static void	ft_history_here_(t_init *init, int hrdg)
// {
// 	t_hstry	*new;

// 	new = NULL;
// 	(void)hrdg;
// 	new = malloc(sizeof(t_hstry) * 1);
// 	new->line = ft_strdup(init->out_put);
// 	new->next = NULL;
// 	new->prev = NULL;
// 	init->hstry_end = new;
// 	init->history = new;
// }

// static void	ft_history_qot_(t_init *init, int hrdg)
// {
// 	t_hstry	*new;

// 	new = NULL;
// 	(void)hrdg;
// 	new = malloc(sizeof(t_hstry) * 1);
// 	new->line = ft_strdup(init->out_put);
// 	new->next = NULL;
// 	init->hstry_end->next = new;
// 	new->prev = init->hstry_end;
// 	init->hstry_end = new;
// }

// void		ft_add_to_history(t_init *init, int hrdg)
// {
// 	t_hstry	*new;
// 	char	*tmp;

// 	new = NULL;
// 	if (init->history == NULL)
// 		ft_history_here_(init, hrdg);
// 	else if (hrdg == 1)
// 	{
// 		tmp = init->hstry_end->line;
// 		init->hstry_end->line = ft_strjoin(init->hstry_end->line,
// 				init->hstry_herdog);
// 		ft_strdel(&init->hstry_herdog);
// 		ft_strdel(&init->key);
// 		ft_strdel(&tmp);
// 	}
// 	else if (hrdg == 2)
// 	{
// 		tmp = init->hstry_end->line;
// 		init->hstry_end->line = ft_strdup(init->out_put);
// 		ft_strdel(&tmp);
// 	}
// 	else
// 		ft_history_qot_(init, hrdg);
// }
