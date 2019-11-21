/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 02:28:02 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 19:12:29 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_printf_fd(int fd, char *format, ...)
{
	va_list	lst;

	va_start(lst, format);
	ft_vprintf(fd, &lst, format);
	va_end(lst);
}

t_printf_params	*ft_init_printf(char *format)
{
	t_printf_params *param;

	param = (t_printf_params *)malloc(sizeof(t_printf_params));
	param->format = format;
	param->str = ft_strnew(0);
	return (param);
}

void			ft_append(t_printf_params *param)
{
	char	*str;
	char	*tmp;

	str = ft_strnew(1);
	str[0] = *param->format;
	str[1] = '\0';
	tmp = param->str;
	param->str = ft_strjoin(param->str, str);
	free(tmp);
	free(str);
}

void			ft_vprintf(int fd, va_list *list, char *format)
{
	t_printf_params	*param;

	param = ft_init_printf((char *)format);
	param->list = list;
	while (*param->format)
	{
		if (*param->format == '%')
			while (*(++param->format))
			{
				param->leading = 0;
				param->padding = 0;
				ft_getflags(param);
				ft_csd(param);
				break ;
			}
		else
			ft_append(param);
		param->format++;
	}
	ft_putstr_fd(param->str, fd);
	va_end(*param->list);
	free(param->str);
	free(param);
}

void			ft_printf(char *format, ...)
{
	va_list	lst;

	va_start(lst, format);
	ft_vprintf(1, &lst, format);
	va_end(lst);
}
