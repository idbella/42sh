/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:30:51 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/08 19:11:22 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	control_subtitution(char *token, char **s1, int *j)
{
	char	*line;
	char	*buffer;
	t_job	*head;
	int		p[2];

	(void)j;
	(void)s1;
	line = ft_strsub(token, 1, ft_strlen(token) - 2);
	// printf("line: %s\n", line);
	pipe(p);
	get_shell_cfg(0)->interractive = 0;
	if (!fork())
	{
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
		if ((head = parse(line)))
			exec(head);
		exit(0);
	}
	wait(NULL);
	close(p[1]);
	// *s1 = NULL;
	while (get_next_line(p[0], '\n',&buffer))
	{
		// printf("buffer: %s\n", buffer);
		if (!*s1)
		{
			*s1 = ft_strdup(buffer);
		}
		else
		{
			*s1 = ft_strjoin(*s1, buffer);
		}
		
	}
	close(p[0]);
}
