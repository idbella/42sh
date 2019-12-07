/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <mmostafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:46:25 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/07 13:38:25 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		check_param(char *param)
{
	int		i;

	i = 0;
	if (param[ft_strlen(param) - 1] == ':')
		return (-1);
	while (param[i])
	{
		if (param[i] == ':' &&
			(param[i + 1] != '-' && param[i + 1] != '+' &&
			 param[i + 1] != '=' && param[i + 1] != '?'))
			return (-1);
		i++;
	}
	return (0);
}

char	*get_param_expan(char *param_expan)
{
	t_param_expan_st	param_word;
	char				*res;

	param_word.word = NULL;
	param_word.param = NULL;
	param_word.type = 0;
	param_word.operation_type = 0;
	if (param_expan[ft_strlen(param_expan) - 1] == ':')
		return (NULL);
	split_param_expan(param_expan, &param_word);
//	printf("PARAM == %s\nWORD == %s\nTYPE == %c\nOPR_TYPE == %c\n", param_word.param, param_word.word,  param_word.type, param_word.operation_type);
	if (!ft_strlen(param_word.param))
	{
		ft_strdel(&param_word.param);
		ft_strdel(&param_word.word);
		return (NULL);
	}
	if (ft_isdigit(param_word.param[0]) && ft_isalphanum(param_word.param))
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

