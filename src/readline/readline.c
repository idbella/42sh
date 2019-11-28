/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:50:50 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 12:09:41 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_init_readline(void)
{
	return ;
}

char	*readline(char *prompt, char opt)
{
	char	*line;

	opt = 0;
	ft_printf("%s", prompt);
	get_next_line(0, &line);
	return (line);
}

