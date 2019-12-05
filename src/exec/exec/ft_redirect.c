/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:00:43 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/04 11:25:09 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_chmod(t_redir *redir)
{
	if (redir->type != O_RDONLY)
	{
		redir->type |= O_CREAT;
		if (!(redir->type & O_APPEND))
			redir->type |= O_TRUNC;
		else
			redir->type |= O_WRONLY;
	}
}

int		ft_getfile(int fdout, t_redir *io)
{
	int	fd;

	ft_chmod(io);
	if ((fd = open(io->file, io->type, 0644)) < 0)
	{
		if (io->type == O_RDONLY)
			ft_printf_fd(fdout, "42sh: no such file or directory: %s\n",
				io->file);
		else
			ft_printf_fd(fdout, "42sh: permission denied: %s\n",
			io->file);
		return (0);
	}
	if (io->src_fd == BOTH_FDS)
	{
		dup2(fd, 1);
		dup2(fd, 2);
	}
	else
		dup2(fd, io->src_fd);
	close(fd);
	return (1);
}

int		ft_redirect(int fdout, t_redir *red)
{
	while (red)
	{
		if (red->type == FD_AGGR && red->dst_fd == -1)
		{
			ft_printf_fd(2, "42sh : ambiguous redirect\n");
			return (0);
		}
		if (red->file)
		{
			if (!ft_getfile(fdout, red))
				return (0);
		}
		else if (red->type == CLOSE_FD)
			close(red->src_fd);
		else if (dup2(red->dst_fd, red->src_fd) == -1)
		{
			ft_printf_fd(fdout, "42sh %d: bad file descriptor\n", red->dst_fd);
			return (0);
		}
		red = red->next;
	}
	return (1);
}
