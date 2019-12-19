/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:30:51 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/19 10:43:58 by yoyassin         ###   ########.fr       */
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

int			exec_(char *line)
{
	t_job	*head;
	pid_t	pid;
	int		p[2];

	if (pipe(p) != 0)
		exit(EXIT_FAILURE);
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
	close(p[1]);
	return (p[0]);
}

void		get_buffer(char **str, int pipe_fd, char type)
{
	char	*buffer;
	int		i;

	*str = NULL;
	while (get_next_line(pipe_fd, '\n', &buffer))
	{
		if (buffer && ft_strlen(buffer))
		{
			*str = !(*str) ? ft_strdup(buffer) : *str;
			if (type)
				*str = ft_join("%f%c%f", *str, '\n', buffer);
			else
			{
				*str = ft_join("%f%c%f", *str, BLANK, buffer);
				i = 0;
				while ((*str)[i])
				{
					if ((*str)[i] == ' ')
						(*str)[i] = BLANK;
					i++;
				}
			}
		}
	}
}

char		*control_subtitution(char *token, char type)
{
	char	*line;
	char	*str;
	int		pipe_fd;

	str = NULL;
	line = ft_strsub(token, 1, ft_strlen(token) - 2);
	pipe_fd = exec_(line);
	get_buffer(&str, pipe_fd, type);
	close(pipe_fd);
	return (str);
}
