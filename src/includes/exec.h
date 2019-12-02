/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:44:26 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/02 08:31:56 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "parser.h"
# include <sys/stat.h>
# include "libft.h"
# include "builtins.h"

typedef struct  stat t_stat;

void	ft_init_exec();
int		exec(t_job *tokens);
void	ft_fork(t_params *params,
                t_process *process, t_function *func);
void	ft_restorestd(char stdin, char stdout, char stderr);
int		ft_redirect(int fdout, t_redir *red);
char	*ft_findfile(char *name, char **error, char add);
char	ft_exec_job(t_params *params, t_process *lst);
char	*getfullpath(char *name);
#endif
