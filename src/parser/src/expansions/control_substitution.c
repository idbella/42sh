/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:30:51 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/08 21:36:53 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	control_subtitution(char *token, char **s1, int *j)
{
	char	*line;
	char	*buffer;
	t_job	*head;
	int		p[2];
	char	*str;
	pid_t	pid;

	(void)j;
	(void)s1;
	line = ft_strsub(token, 1, ft_strlen(token) - 2);
	//printf("line: %s\n", line);
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
	// *s1 = NULL;
	while (get_next_line(p[0], '\n',&buffer))
	{
		//printf("buffer: %s\n", buffer);
		if (!str)
			str = ft_strdup(buffer);
		else
			str = ft_join("%s %s", str , buffer);
		*s1 = str;
	}
	close(p[0]);
}
