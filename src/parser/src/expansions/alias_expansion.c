/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:47:49 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/10 13:03:41 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	join_char(char **str, char c)
{
	char	*joined;
	int		len;
	int		i;

	len = ft_strlen(*str);
	joined = ft_strnew(len + 1);
	i = 0;
	while (i < len)
	{
		joined[i] = (*str)[i];
		i++;
	}
	joined[len] = c;
	free(*str);
	*str = joined;
}

char	*gather_tokens(t_token *tokens)
{
	char	*str;
	int		j;
	int		n;

	str = NULL;
	n = 1;
	while (tokens)
	{
		j = 0;
		// printf("n : %d\n", n++);
		while (tokens->list[j])
		{
			if (!str)
				str = ft_strdup(tokens->list[j]);
			else
				str = ft_join("%s %s", str, tokens->list[j]);
			j++;
		}
		if (tokens->type == AND || tokens->type == OR)
			join_char(&str, tokens->type);
		if (tokens->type != SEMI_COL)
			join_char(&str, tokens->type);
		tokens = tokens->next;
	}
	return (str);
}

t_token	*get_tokens(t_token **head, char *line)
{
	char	*cmd_chain;
	int		i;
	int		old_i;
	t_token	*token;
	t_token	*tail;
	char	*str;

	// cmd_chain = ft_strsplit(line, SEMI_COL);
	*head = NULL;
	tail = NULL;
	token = NULL;
	cmd_chain = line;
	i = 0;
	old_i = 0;
	while (cmd_chain[i])
	{
		if (token && (cmd_chain[i] == BG || cmd_chain[i] == AND ||
		cmd_chain[i] == OR || cmd_chain[i] == PIPE || cmd_chain[i] == SEMI_COL))
		{
			old_i += i - old_i;
			token->type = cmd_chain[i];
			i = (cmd_chain[i] == AND || cmd_chain[i] == OR) ? i + 2 : i + 1;
			if (!*head)
				*head = token;
			else
				tail->next = token;
			tail = token;
			token = NULL;
		}
		else
		{
			str = skip_operators(4, cmd_chain, &old_i, &i);
			token = NULL;
			token = (t_token *)malloc(sizeof(t_token));
			token->type = 0;
			token->list = NULL;
			token->sub = NULL;
			token->next = NULL;
			token->list = ft_strsplit(str, BLANK);
		}
	}
	if (token)
	{
		if (!*head)
			*head = token;
		else
			tail->next = token;
		tail = token;
		token = NULL;
	}
	return (*head);
}

char	*extract_arg(char *token, int offset)
{
	int	i;
	int	start;

	i = offset;
	start = 0;
	while (token[i])
	{
		if (token[i] == BLANK)
		{
			while (token[i] && token[i] == BLANK)
				i++;
			start = i;
		}
		else
		{
			while (token[i] && token[i] != BLANK)
				i++;
			return (ft_strsub(token, start, i - start));
		}
	}
	return (NULL);
}

char	*expand_alias(t_token *token, char *alias)
{
	int		i;
	char	*arg;
	t_token *tokens;
	char	*str;

	mark_operators(alias);
	mark_bg_op(alias);
	token->sub = get_tokens(&token->sub, alias);
	tokens = token->sub;
	str = ft_strnew(0);
	while (tokens)
	{
		arg = tokens->list[0];
		i = 0;
		while (*(tokens->list) && arg && ft_strchr(arg, '='))
			arg = tokens->list[++i];
		if (arg)
		{
			if ((alias = ft_getvlaue_bykey(arg, ALIAS)))
				tokens->list[0] = ft_strdup(expand_alias(tokens, ft_strdup(alias)));
		}
		int	j;
		j = 0;
		while (tokens->list[j])
		{
			str = ft_join("%s %s", str, tokens->list[j]);
			j++;
		}
		if (tokens->type == AND || tokens->type == OR)
			join_char(&str, tokens->type);
		join_char(&str, tokens->type);
		tokens = tokens->next;
	}
	return (str);
}

t_token	*alias_expansion(char **line)
{
	t_token			*tokens;
	char			*arg;
	char			*alias;
	int				i;
	t_token			*tmp;

	tokens = NULL;
	arg = NULL;
	tokens = get_tokens(&tokens, *line);
	tmp = tokens;
	while (tokens)
	{
		arg = tokens->list[0];
		i = 0;
		while (*(tokens->list) && arg && ft_strchr(arg, '='))
			arg = tokens->list[++i];
		if (arg)
		{
			if ((alias = ft_getvlaue_bykey(arg, ALIAS)))
				tokens->list[0] = expand_alias(tokens, ft_strdup(alias));
			// printf("tokens->list[0]: %s\n", tokens->list[0]);
		}
		tokens = tokens->next;
	}
	return (tmp);
}
