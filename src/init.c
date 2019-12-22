/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:12:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 17:34:52 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_sigint_handler(int sig)
{
	char	*prompt;

	sig = 0;
	prompt = ft_getprompt();
	ft_printf("%s", prompt);
	free(prompt);
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
		ut = ptr + i;
		if (ut->ut_type == USER_PROCESS)
			return (ut->ut_user);
		i += 628;
	}
	return (NULL);
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
	ft_addtohashmap("?", "0", INTERN);
	shell->init = init;
	shell->pwd = ft_strdup(ft_getenv("PWD"));
	shell->last_exit = 0;
	shell->subshell = 0;
	shell->id = 0;
	shell->abort = 0;
}
