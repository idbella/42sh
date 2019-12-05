/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:47:49 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/05 12:03:01 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*get_tokens(t_token **head, char *line)
{
	char	**cmd_chain;
	int		i;
	int		old_i;
	t_token	*token;
	t_token	*tail;

	cmd_chain = ft_strsplit(line, SEMI_COL);
	while (*cmd_chain)
	{
		i = 0;
		old_i = 0;
		while ((*cmd_chain)[i])
		{
			if (token && ((*cmd_chain)[i] == BG || (*cmd_chain)[i] == AND
			|| (*cmd_chain)[i] == OR || (*cmd_chain)[i] == PIPE))
			{
				old_i += i - old_i;
				token->type = (*cmd_chain)[i];
				i = ((*cmd_chain)[i] == AND || (*cmd_chain)[i] == OR) ? i + 2 : i + 1;
				if (!*head)
					*head = token;
				else
					tail->next = token;
				tail = token;
				token = NULL;
			}
			else
			{
				token = malloc(sizeof(t_token));
				token->expanded = 0;
				token->r = 0;
				token->up = NULL;
				token->next = NULL;
				token->index = 0;
				token->sub = NULL;
				token->type = 0;
				token->list = ft_strsplit(skip_operators(4, *cmd_chain, &old_i, &i), BLANK); 
			}
		}
		cmd_chain++;
	}
	if (!*head)
		*head = token;
	else
		tail->next = token;
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

t_token	*expand_alias(t_token *token, char *alias)
{
	int		i;
	char	*arg;
	t_token *tokens;
	t_token	*rp = NULL;

	mark_operators(alias);
	mark_bg_op(alias);
	token->sub = get_tokens(&token->sub, alias);
	tokens = token->sub;
	while (tokens)
	{
		arg = tokens->list[0];
		i = 0;
		while (*(tokens->list) && ft_strchr(arg, '='))
			arg = tokens->list[++i];
		if (arg)
		{
			if ((alias = ft_getvlaue_bykey(arg, ALIAS)))
			{
				rp = expand_alias(tokens, alias);
				
				return (token);
			}
		}
		tokens = tokens->next;
	}
	return (token);
}

void	gather_tokens(t_token *tokens, char **str)
{
	// printf("pr_token: %s type : %d expanded: %d\n", tokens->list[0], tokens->type, tokens->expanded);
	if (tokens->sub)
	{
		// printf("sub: \n");
		gather_tokens(tokens->sub, str);
		while (tokens && !tokens->r)
		{
			// printf("token: %s type: %d\n", tokens->list[0], tokens->type);
			*str = ft_strjoin(*str ? *str : ft_strnew(0) , " ");
			*str = ft_strjoin(*str, tokens->list[0]);
			*str = ft_strjoin(*str, &tokens->type);
			tokens = tokens->next;
		}
	}
}

void	__print(t_token *tokens)
{
	printf("token : %s type : %d index: %d\n", tokens->list[0], tokens->type, tokens->index);
	if (tokens->sub)
	{
		__print(tokens->sub);
		if (tokens->next)
			__print(tokens->next);
	}
}

t_token	*alias_expansion(char **line)
{
	t_token			*tokens;
	char			*arg;
	char			*alias;
	char			*str;
	int				i;
	t_token			*rp;

	tokens = NULL;
	arg = NULL;
	tokens = get_tokens(&tokens, *line);
	t_token *tmp = tokens;
	while (tokens)
	{
		arg = tokens->list[0];
		i = 0;
		while (tokens->list && ft_strchr(arg, '='))
			arg = tokens->list[++i];
		if (arg)
		{
			if ((alias = ft_getvlaue_bykey(arg, ALIAS)))
			{
				rp = expand_alias(tokens, alias);
				// tokens->list[0] = NULL;
				// while (rp)
				// {
				// 	if (!tokens->list[0])
				// 		tokens->list[0] = ft_strdup(rp->list[0]);
				// 	int j = 1;
				// 	while (rp->list[j])
				// 	{
				// 		tokens->list[0] = ft_strjoin(tokens->list[0], &rp->type);
				// 		tokens->list[0] = ft_strjoin(tokens->list[0], rp->list[j]);
				// 		j++;
				// 	}
				// 	rp = rp->next;
				// }
			}
		}
		tokens = tokens->next;
	}
	str = NULL;
	tokens = tmp;
	while (tokens)
	{
		// if (tokens->sub)
		// 	__print(tokens->sub);
		printf("r_t: %s type : %d\n", tokens->list[0], tokens->type);
		str = NULL;
		tokens = tokens->next;
	}
	return (tmp);
}