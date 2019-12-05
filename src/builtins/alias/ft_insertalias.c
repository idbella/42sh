/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertalias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 14:46:11 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/03 19:16:54 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// void	ft_insert(t_job *job, t_token *prev,
// 					t_token_list *tokens, t_token *new)
// {
// 	t_token *tmp;

// 	if (!prev)
// 	{
// 		tmp = new;
// 		while (new->next)
// 			new = new->next;
// 		new->next = tokens->head->next;
// 		tokens->head = tmp;
// 		tmp = tokens->head;
// 	}
// 	else
// 	{
// 		prev->next = new;
// 		while (new->next)
// 			new = new->next;
// 		new->next = token->next;
// 	}
// 	free(token);
// }

size_t	ft_arrcount(char **arr)
{
	size_t	i;

	i = 0;
	while (*arr)
	{
		arr++;
		i++;
	}
	return (i);
}

void	ft_insert_at(t_job *job, t_process *proc, size_t index)
{
	size_t		i;
	char		**args;
	size_t		i2;
	size_t		i3;
	//t_job		*next;

	i = 0;
	size_t	arr1count;
	size_t	arr2count;
	arr1count = ft_arrcount(job->processes->arg);
	arr2count = ft_arrcount(proc->arg);
	args = ft_memalloc(sizeof(char *) * (arr1count + arr2count + 1));
	i2 = 0;
	i3 = 0;
	while (i < arr1count + arr2count)
	{
		if (i >= index && i < index + arr1count)
		{
			args[i] = job->processes->arg[i2++];
		}
		else
		{
			if (index != i3)
			{
				args[i] = proc->arg[i3];
			}
			else
				i--;
			i3++;
		}
		i++;
	}
	// next = job->next;
	// job->next = next;
	//current->next = job->next;
	//job->processes->redir->next = proc->redir;
	proc->redir = job->processes->redir;
	proc->arg = args;
}
