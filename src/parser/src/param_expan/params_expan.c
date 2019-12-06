/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:46:25 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/06 16:01:36 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_param_expan(char *param_expan)
{
	t_param_expan_st	param_word;
	char				*res;

	param_word.word = NULL;
	param_word.param = NULL;
	param_word.type = 0;
	param_word.operation_type = 0;
	split_param_expan(param_expan, &param_word);
	if (!ft_strlen(param_word.param))
	{
		ft_strdel(&param_word.param);
		ft_strdel(&param_word.word);
		return (NULL);
	}
	if (ft_isdigit(param_word.param[0]) && param_word.param[1] &&
		ft_isalnum(*param_word.param + 1))
	{
		ft_strdel(&param_word.param);
		ft_strdel(&param_word.word);
		return (NULL);
	}
	res = operators_manager(&param_word);
	ft_strdel(&param_word.param);
	ft_strdel(&param_word.word);
	return (res);
}

