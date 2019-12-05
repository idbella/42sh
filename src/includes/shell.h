/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:40:36 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 16:40:27 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include <fcntl.h>
# include "datatypes.h"
# include "readline.h"
# include "parser.h"
# include "exec.h"
# include "libft.h"
# include "builtins.h"
# include "jobcontrol.h"

# define EXIT_ON_EOT 0
# define RETURN_ON_EOT 1

t_shell		*get_shell_cfg(t_shell *new);
void		init_(t_shell *shell, char **env);
#endif
