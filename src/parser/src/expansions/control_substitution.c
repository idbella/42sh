/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:30:51 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/14 11:14:43 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*control_subtitution(char *token, char type)
{
	char	*line;
	char	*buffer;
	t_job	*head;
	int		p[2];
	char	*str;
	pid_t	pid;

	line = ft_strsub(token, 1, ft_strlen(token) - 2);
	// line = ft_strctrim(token, '(');
	// line = ft_strctrim(token, ')');
	printf("2_line: %s\n", line);
	pipe(p);
	if (!(pid = fork()))
	{
		get_shell_cfg(0)->interractive = 0;
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
			// dprintf(2, "buffer : %s\n", buffer);
			if (!str)
				str = ft_strdup(buffer);
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
