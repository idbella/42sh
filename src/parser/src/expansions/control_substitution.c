/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:30:51 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/18 19:46:56 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ctl_subst(char *s, char *tmp, char **str, char type)
{
	char	*param;
	char	*exp;
	int		i;

	i = 0;
	param = NULL;
	exp = NULL;
	param = get_dollar_var(tmp, &i, 0);
	if (s[ft_strlen(param) + 1])
		*str = ft_strdup(s + ft_strlen(param) + 1);
	if ((exp = control_subtitution(param, type)) && ft_strlen(exp))
	{
		if (*str)
			*str = ft_fstrjoin(exp, *str);
		else
		{
			*str = ft_strdup(exp);
			free(exp);
		}
	}
	free(param);
}

char		*control_subtitution(char *token, char type)
{
	char	*line;
	char	*buffer;
	t_job	*head;
	int		p[2];
	char	*str;
	pid_t	pid;
	int		i;

	line = ft_strsub(token, 1, ft_strlen(token) - 2);
	pipe(p);
	if (!(pid = fork()))
	{
		get_shell_cfg(0)->subshell = 1;
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
		if ((head = parse(line)))
			exec(head);
		exit(0);
	}
	waitpid(pid, 0, 0);
	str = NULL;
	close(p[1]);
	while (get_next_line(p[0], '\n', &buffer))
	{
		if (buffer && ft_strlen(buffer))
		{
			// dprintf(2, "\ntype: %d buffer : %s \n", type, buffer);
			if (!str)
			{
				str = ft_strdup(buffer);
				i = 0;
				while (str[i])
				{
					if (str[i] == ' ')
						str[i] = BLANK;
					i++;
				}
			}
			else
			{
				if (type)
					str = ft_join("%s%c%s", str, '\n', buffer);
				else
					str = ft_join("%s%c%s", str, BLANK, buffer);
			}
		}
	}
	close(p[0]);
	// printf("str: %s\n", str);
	return (str);
}
