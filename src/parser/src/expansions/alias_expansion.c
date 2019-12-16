/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:47:49 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/16 14:46:16 by yoyassin         ###   ########.fr       */
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
		// if (tokens->type != SEMI_COL)
		join_char(&str, tokens->type);
		tokens = tokens->next;
	}
	return (str);
}

static void	append(t_token **head, t_token **tail, t_token **token)
{
	if (!*head)
		*head = *token;
	else
		(*tail)->next = *token;
	*tail = *token;
	*token = NULL;
}

void			add_spaces(char **str)
{
	int		j;
	int		i;
	char	*s[3];

	s[0] = NULL;
	s[1] = NULL;
	s[2] = NULL;
	j = 0;
	while ((*str)[j])
	{
		if ((*str)[j] == OUT_RED_OP || (*str)[j] == IN_RED_OP
		|| (*str)[j] == APP_OUT_RED_OP || (*str)[j] == HEREDOC_OP)
		{
			i = (j > 0) ? j - 1 : 0;
			if (!ft_isdigit((*str)[i]) && (*str)[i] != '&')
			{
				s[0] = ft_strsub(*str, 0, j);
				join_char(&s[0], BLANK);
				s[1] = ft_strdup((*str) + j);
				s[2] = ft_fstrjoin(s[0], s[1]);
				j = (*str)[j] == ((*str)[j] == OUT_RED_OP || (*str)[j] == IN_RED_OP) ?
					j + 2 : j + 3;
				free(*str);
				*str = s[2];
			}
			else
			{
				j++;
				continue;
			}
		}
		else
			j++;
	}
}

static t_token	*get_node(char *cmd_chain, int *old_i, int *i)
{
	t_token	*token;
	char	*str;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		exit(EXIT_FAILURE);
	token->type = 0;
	token->list = NULL;
	token->sub = NULL;
	token->next = NULL;
	if ((str = skip_operators(4, cmd_chain, old_i, i)))
	{
		add_spaces(&str);
		token->list = ft_strsplit(str, BLANK);
		free(str);
	}
	return (token);
}

t_token	*get_tokens(t_token **head, char *cmd_chain)
{
	int		i;
	int		old_i;
	t_token	*token;
	t_token	*tail;

	tail = NULL;
	token = NULL;
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
			append(head, &tail, &token);
		}
		else
			token = get_node(cmd_chain, &old_i, &i);
	}
	if (token)
		append(head, &tail, &token);
	return (*head);
}

// int		circular(t_alias *h, char *arg, char *alias)
// {
// 	t_alias	*c;

// 	c = NULL;
// 	if (!(h->next = malloc(sizeof(t_alias))))
// 		exit(EXIT_FAILURE);
// 	// h->next->prev = h;
// 	h->next->next = NULL;
// 	h->next->key = ft_strdup(arg);
// 	c = h->next;
// 	printf("*arg : %s alias:  %s\n", arg, alias);
// 	return (1);
// 	while (c)
// 	{
// 		if (c->prev && ft_strequ(c->key, alias))
// 		{
// 			// printf("c->key: %s alias: %s\n", c->key, alias);
// 			return (1);
// 		}
// 		c = c->prev;
// 	}
// 	return (0);
// }
// l=ls ls=l q=l a=l a->l->ls->l l->ls->l

int		match(t_alias *h, t_alias *t)
{
	t_alias	*iter;

	iter = h;
	while (iter)
	{
		if (!iter->next)
			break ;
		if (ft_strequ(iter->key, t->key))
		{
			// printf("match : %s\n", iter->key)
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

int		circular(t_alias *h, t_alias **t, char *alias)
{
	t_alias	*c;
	// char	*arg;

	c = NULL;
	// arg = alias;
	// while ((alias = ft_getvlaue_bykey(arg, ALIAS)))
	// {
	c = malloc(sizeof(t_alias));
	c->key = ft_strdup(alias);
	c->next = NULL;
	// printf("<<c->key : %s\n", c->key);
	if (!h->next)
		h->next = c;
	else
		(*t)->next = c;
	*t = c;
	if (match(h, *t))
		return (1);
	// arg = c->key;
	// }
	return (0);
}

static t_token	*get_sub_token(t_token *token, char *alias, char **str)
{
	mark_operators(alias);
	mark_bg_op(alias);
	token->sub = get_tokens(&token->sub, alias);
	*str = ft_strnew(0);
	return (token->sub);
}

void	combine(t_token *tokens, char **str)
{
	int	j;

	j = 0;
	while (tokens->list[j])
	{
		*str = ft_fstrjoin(*str, ft_strdup(" "));
		*str = ft_fstrjoin(*str, tokens->list[j]);
		j++;
	}
	if (tokens->type == AND || tokens->type == OR)
		join_char(str, tokens->type);
	join_char(str, tokens->type);
}

char	*expand_alias(t_token *token, char *alias, t_alias *h, char op, t_alias **t)
{
	int		i;
	char	*arg;
	t_token *tokens;
	char	*str;
	// t_alias	*t;

	tokens = get_sub_token(token, alias, &str);
	while (tokens)
	{
		arg = tokens->list[0];
		i = 0;
		while (*(tokens->list) && arg && ft_strchr(arg, '='))
			arg = tokens->list[++i];
		if (arg)
		{
			if ((alias = ft_getvlaue_bykey(arg, ALIAS))
			&& !circular(h, t, arg))
			{
				arg = DUPL(expand_alias(tokens, DUPL(alias), h, 1, t));
				free(tokens->list[i]);
				tokens->list[i] = arg;
				(void)op;
				// if (op)
				// 	free(alias);
			}
			else if (alias)
				tokens->list[i] = ft_strdup((*t)->key);
		}
		combine(tokens, &str);
		tokens = tokens->next;
	}
	return (str);
}

void	update_token(t_token *tokens, char *alias, char **arg, int i)
{
	t_alias			*h = NULL;
	t_alias			*t = NULL;

	if (!(h = (t_alias *)malloc(sizeof(t_alias))))
		exit(EXIT_FAILURE);
	h->key = ft_strdup(*arg);
	// printf(">> %s\n", h->key);
	h->next = NULL;
	*arg = expand_alias(tokens, alias, h, 0, &t);
	free(tokens->list[i]);
	tokens->list[i] = *arg;
	free(alias);
}

t_token	*alias_expansion(char *line)
{
	t_token			*tokens;
	char			*arg;
	char			*alias;
	int				i;
	t_token			*tmp;

	tokens = NULL;
	arg = NULL;
	tokens = get_tokens(&tokens, line);
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
				update_token(tokens, ft_strdup(alias), &arg, i);
		}
		tokens = tokens->next;
	}
	return (tmp);
}
