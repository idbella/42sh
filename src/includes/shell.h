/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:40:36 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 12:13:14 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include <fcntl.h>
# include "readline.h"
# include "parser.h"
# include "exec.h"
# include "libft.h"
# include "builtins.h"
# define EXIT_ON_EOT 0
# define RETURN_ON_EOT 1

typedef struct	s_shell
{
	char			**env;
	t_list			**hashmap;
	t_job			*jobs;
	int				last_exit;
}				t_shell;

t_shell		*get_shell_cfg(t_shell *new);
void		init_(t_shell *shell, char **env);
#endif
