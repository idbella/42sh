/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:25:14 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/19 17:59:38 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	-Check if line is properly quoted.
**	-Mark the operators '|' '||' '&&' '>' ... + spaces.
**	-Syntax checking.
**  -TO DO: - revise syntax checking + add support for ${} and $(). -DONE.
**			- fix alias expansion. -DONE.
**			- fix circular. - DONE.
**			- fix D_QUOTES. -Done.
**			- fix ${?} -partially
**			- heredoc. -partially ctrl+c
**			- search for errors.
**			- norminette and leaks.
**			- more tests.
*/

int			is_not_blank(char *line, int j, int i)
{
	char	valid;

	valid = 0;
	while (j < i)
	{
		if (ft_isprint((int)line[j]))
			valid = 1;
		j++;
	}
	return (valid);
}

int			is_word(char *word)
{
	while (*word)
	{
		if (!ft_isalnum(*word) && *word != '_' && *word != '-')
			return (0);
		word++;
	}
	return (1);
}

t_job		*parse(char *input)
{
	char		**cmd_chain;
	char		*line;
	t_job		*head;
	t_token		*tokens;

	head = NULL;
	if (!(line = pre_parse(input)))
		return (NULL);
	tokens = alias_expansion(line);
	free(line);
	line = gather_tokens(tokens);
	highlight_ops(line);
	if (syntax_error(&line))
		return (NULL);
	cmd_chain = ft_strsplit(line, SEMI_COL);
	if (!(head = get_jobs(cmd_chain, get_bg_jobs(line))))
	{
		free_array(cmd_chain);
		free(line);
		return (NULL);
	}
	free_array(cmd_chain);
	free(line);
	return (head);
}
