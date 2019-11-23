/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:07:58 by mfarhi            #+#    #+#             */
/*   Updated: 2019/11/23 14:02:03 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_fstrjoin(char const *s1, char const *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free((char *)s1);
	free((char *)s2);
	return (str);
}
