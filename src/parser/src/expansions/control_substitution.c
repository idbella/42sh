/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:30:51 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/02 11:30:59 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	control_substitution(char *token, char **s1, int *j)
{
	char	*line;
	char	*buffer;
	t_job	*head;
	int		p[2];
	char	*option[2] = {"-a", NULL};

	(void)j;
	(void)s1;
	line = ft_strsub(token, 1, ft_strlen(token) - 2);
	pipe(p);
	if ((head = parse(line)))
	{
		if (!fork())
		{
			dup2(p[1], 1);
			close(p[1]);
			close(p[0]);
			if (!fork())
			{
				execve("/bin/ls", option, NULL);
			}
			wait(NULL);
			exit(0);
		}
		wait(NULL);
		close(p[1]);
		while (get_next_line(p[0], &buffer))
			printf("buffer: %s\n", buffer);
		close(p[0]);
	}
	// printf("cmd : %s\n", line);
}
