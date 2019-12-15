/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 01:21:25 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/15 13:55:42 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <assert.h>
size_t	ft_strlen(const char *s)
{
	size_t lenght;

	lenght = 0;
	assert(s);
	if (s)
		while (*s != '\0')
		{
			lenght++;
			s++;
		}
	return (lenght);
}
