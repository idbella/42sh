/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:38:46 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/07 11:07:33 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H
# include "libft.h"
#include <termios.h>
# define BUILTINS_COUNT 15
# define TESTFUNCTIONS_COUNT 20

typedef struct	s_redir
{
	int				type;
	int				src_fd;
	int				dst_fd;
	char			*file;
	struct s_redir	*next;
}				t_redir;

typedef struct	s_process
{
	char				**arg;
	pid_t				pid;
	int					status;
	int					p0;
	t_redir				*redir;
	int					flag;
	char				*heredoc;
	int					heredoc_fd;
	char				exited;
	char				stoped;
	char				*name;
	char				signaled;
	struct s_process	*next;
}				t_process;

typedef struct	s_job
{
	t_process		*processes;
	pid_t			pgid;
	char			*command;
	int				return_val;
	int				flag;
	int				id;
	char			suspended;
	char			killed;
	char			foreground;
	char			notified;
	char			sub;
	struct s_job	*next;
}				t_job;

typedef struct		s_map
{
	void	*key;
	void	*value;
	int		hits;
	char	type;
	char	exported;
}					t_map;

typedef struct	s_shell
{
	char			interractive;
	t_map			builtins[BUILTINS_COUNT];
	t_list			**hashmap;
	t_job			*jobs;
	int				last_exit;
}				t_shell;

typedef struct			s_params
{
	int				forkbuiltins;
	int				fd;
	int				argv_index;
	int				pipe_stdin;
	t_list			*tmpenv;
	t_job			*job;
}						t_params;

typedef struct			s_container
{
	t_list			*list;
	t_job			*current;
	t_list			*notify;
	t_job			*prev;
	uint8_t			last_status;
	char			time_to_exit;
	int				stdcopy;
	t_list			*last_aliases;
	t_params		*params;
	t_list			*env;
	char			**test_operators;
	t_map			testfunctions[20];	
	struct termios	*term;
}						t_container;

#endif
