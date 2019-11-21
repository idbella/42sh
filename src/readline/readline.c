/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:50:50 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/21 17:16:22 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*readline(char *prompt, char opt)
{
	char	*line;

	opt = 0;
	ft_printf("%s", prompt);
	get_next_line(0, &line);
	return (line);
}

