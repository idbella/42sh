/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 13:35:11 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/08 13:22:40 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_printusage(int c)
{
	ft_printf("42sh: fc: -%c: invalid option\n", -c);
	ft_printf("usage :\n\
	fc [-r] [-e editor] [first [last]]\n\
	fc -l [-nr] [first [last]]\n\
	fc -s [old=new] [first]\n");
	return (1);
}

int		ft_fc(char **args)
{
	char	options[127];
	int		index;

	if ((index = ft_getopt(args, options, "relns")) < 0)
		return (ft_printusage(index));
	ft_printf("index = %d\n", index);
	//index = 0;
	// while (index < 127)
	// {
	// 	if (options[index])
	// 		ft_printf("%c\n", index);
	// 	index++;
	// }
	if (options['e'])
		ft_run_fc_editor(args + index);
	return (0);
}
