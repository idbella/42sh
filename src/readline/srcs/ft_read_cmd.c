/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 20:15:42 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/01 22:36:21 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	ft_read_more(char *buffer, t_init *init, char **t)
{
	char		*tmp;

	init->skip_read = 1;
	tmp = *t;
	if (*t[0] == '\0')
		*t = ft_strdup(buffer);
	else
		*t = ft_strjoin(*t, buffer);
	free(tmp);
}

char	*ft_herd_qout_normal(t_init *init, char *buffer, char **t)
{
	char	*line;

	line = NULL;

	if (init->heredoc_int == 1)
	{
		if ((buffer[0] == 4 && buffer[1] == '\0') &&
			ft_strcmp(init->out_put, "(hr)>") == 0)
		{
			if ((line = ft_heredoc(init->key, init)))
				return (line);
			if ((line = ft_heredoc("\n", init)))
				return (line);
		}
		else
		{
			if ((line = ft_heredoc(*t, init)))
				return (line);
		}
	}
	else if (!(buffer[0] == 4 && buffer[1] == '\0') && init->qoute == 1)
	{
		if (!(line = ft_qoute(*t, init)))
			return (line);
	}
	else if (!(buffer[0] == 4 && buffer[1] == '\0'))
	{
		if ((line = move_cursor_and_mangemant_fonction(*t, init)))
			return (line);
	}
	ft_strdel(t);
	return (NULL);
}

char		*ft_read(char *buffer, int position, t_init *init)
{
	static char	*t;
	char		*tmp;
	char *line;

	line = NULL;
	dprintf(open("/dev/ttys016",O_RDWR),"\nstr = %s\n", buffer);	
	if (t == NULL)
		t = ft_strnew(0);
	if (t[0] == '\n')
		t[0] = '\0';
	if (position < 4)
	{	
		init->skip_read = 0;
		tmp = t;
		t = ft_strjoin(t, buffer);
		ft_strdel(&tmp);
		if ((line = ft_herd_qout_normal(init, buffer, &t)))
			return (line);
	}
	else
		ft_read_more(buffer, init, &t);
	return (NULL);
}

char	*ft_str_acolade(char *str)
{
	int			i;
	int			j;
	char		tmp;
	char		*str_new;

	i = -1;
	j = -1;
	tmp = '\0';
	str_new = ft_strnew(ft_strlen(str));
	while (str[++i])
	{
		if (str[i] == '"' && tmp == '\0')
			tmp = '"';
		else if (str[i] == '\'' && tmp == '\0')
			tmp = '\'';
		else if (str[i] == '"' && tmp == '"')
			tmp = '\0';
		else if (str[i] == '\'' && tmp == '\'')
			tmp = '\0';
		else
			str_new[++j] = str[i];
	}
	return (str_new);
}
