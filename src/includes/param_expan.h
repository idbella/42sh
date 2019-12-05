/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expan.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <mmostafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:15:28 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/04 09:34:52 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_EXPAN_H
# define PARAM_EXPAN_H
# include "libft.h"

typedef struct s_param_expan_st
{
	char	*word;
	char	*param;
	char	type;
	char	operation_type;
}				t_param_expan_st;

char    *rm_ffixers(t_param_expan_st *param_word);
char    *operators_manager(t_param_expan_st *param_word);
void    split_param_expan(char *param_expan, t_param_expan_st *param_word);
char	*get_param_expan(char *param_expan);

#endif
