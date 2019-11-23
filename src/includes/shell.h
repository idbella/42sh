/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:40:36 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/23 13:50:11 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include <fcntl.h>
# include "readline.h"
# include "parser.h"
# include "exec.h"
# include "libft.h"
# define EXIT_ON_EOT 0
# define RETURN_ON_EOT 1

typedef struct	s_shell
{
	t_job			*jobs;
	// t_env			*env;
	int				last_exit;
}				t_shell;

#endif
