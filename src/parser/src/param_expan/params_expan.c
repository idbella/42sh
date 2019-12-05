/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <mmostafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:46:25 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/04 13:33:44 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_param_expan(char *param_expan)
{
	t_param_expan_st	param_word;

	param_word.word = NULL;
	param_word.type = 0;
	param_word.operation_type = 0;
	split_param_expan(param_expan, &param_word);
	/*
	 * after that we get all items about our expresion (param ,word, type, opration_type)
	 *
	 *type have tow possible values A (arithmetic expansions) or P (parameter expansions)
	 *type_operation have four possible values (+, -, =, ?) that we'll traiting them 
	 *
	 * */
	if (!ft_strlen(param_word.param))
		return (NULL);
	else
		return (operators_manager(&param_word));
	return (NULL);
}

