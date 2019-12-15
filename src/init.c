/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:12:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/15 20:56:55 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_sigint_handler(int sig)
{
	sig = 0;
	ft_putstr("\n$> ");
}

t_shell	*get_shell_cfg(t_shell *new)
{
	static t_shell	*sh;

	if (new)
		sh = new;
	return (sh);
}

char	*ft_getusername(void)
{
	int				fd;
	struct stat		st;
	void			*ptr;
	off_t			i;
	struct utmpx	*ut;

	fd = open("/var/run/utmpx", O_RDONLY);
	fstat(fd, &st);
	ptr = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	i = 0;
	while (i < st.st_size)
	{
		ut = ptr+i;
		if (ut->ut_type == USER_PROCESS)
			return (ut->ut_user);
		i += 628;
	}
	return (NULL);
}

char	*ft_getprompt()
{
	char	*path;
	char	*home;
	int		len;
	char	*tmp;
	time_t	t;
	int		status;
	char	*clr;

	time(&t);
	tmp = ctime(&t);
	tmp = ft_strsub(tmp, 11, 8);
	if ((path = ft_getenv("PWD")))
	{
		if ((home = ft_getenv("HOME")))
		{
			len = ft_strlen(home);
			if (ft_strnequ(home, path, len))
			{
				if (*(path + len) == '/')
					path = ft_join("~%s", path + len);
				else
					path = ft_join("~/%s", path + len);
			}
		}
		status = ft_get_last_rvalue();
		clr = "\e[32m";
		if (status)
			clr = "\e[31m";
		return (ft_join("[\e[90m%s\e[0m][%s%03d\e[0m] \e[36m%s $> \e[0m", tmp, clr,get_shell_cfg(0)->id++, path));
	}
	return ft_strdup("\e[32m 42sh\e[33m $> \e[0m");
}

void	init_(t_shell *shell, char **env, t_init *init)
{
	signal(SIGINT, ft_sigint_handler);
	get_shell_cfg(shell);
	shell->interractive = 1;
	ft_init_exec();
	ft_init_builtins(env);
	ft_init_readline(init);
	ft_read_file_(init);
	ft_addtohashmap("FCEDIT", "vim", INTERN);
	shell->init = init;
	shell->last_exit = 0;
	shell->subshell = 0;
	shell->id = 0;
}
