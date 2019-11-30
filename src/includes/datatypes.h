/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:38:46 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/30 15:56:03 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H
# include "libft.h"
# define BUILTINS_COUNT 10

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
	char			*cmd;
	char			suspended;
	char			killed;
	char			foreground;
	char			notified;
	struct s_job	*next;
	t_redir			*gr_redir;
	struct s_job	*sub;
	struct s_job	*group;
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
	char			**env;
	t_list			**hashmap;
	t_job			*jobs;
	int				last_exit;
}				t_shell;

typedef struct			s_container
{
	t_list			*list;
	t_job			*current;
	t_list			*notify;
	t_job			*last;
	int				last_status;
	char			time_to_exit;
	int				stdcopy;
	t_list			*last_aliases;
	t_list			*env;
}						t_container;

typedef struct			s_params
{
	int				fd;
	int				argv_index;
	int				pipe_stdin;
	t_list			*tmpenv;
	t_job			*job;
}						t_params;

#endif
