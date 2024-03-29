/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:52:18 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/07 13:11:11 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	only_whitespaces(const char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] != ' ')
			return (0);
	}
	return (1);
}

t_token	*create_token(char *token_value)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = UNDEFINED;
	new_token->value = token_value;
	new_token->left = NULL;
	new_token->right = NULL;
	new_token->parent = NULL;
	new_token->input = 0;
	new_token->output = 1;
	return (new_token);
}

int	add_token(t_tokenizer_utils *u, char *token_value)
{
	int		i;

	if (u->size + 1 >= u->capacity)
	{
		u->new_capacity = u->capacity * 2;
		u->new_tokens = (t_token **)malloc(u->new_capacity * sizeof(t_token *));
		if (!u->new_tokens)
			return (0);
		i = -1;
		while (++i < u->size)
			u->new_tokens[i] = u->tokens[i];
		free(u->tokens);
		u->tokens = u->new_tokens;
		u->capacity = u->new_capacity;
	}
	u->tokens[u->size] = create_token(token_value);
	if (u->tokens[u->size] == NULL)
		return (0);
	(u->size)++;
	u->tokens[u->size] = NULL;
	return (1);
}

static int	route_handler(t_tokenizer_utils *u, const char *input)
{
	if ((u->c == '|' || u->c == '<' || u->c == '>')
		&& u->quoting_status == UNQUOTED)
	{
		if (!handle_special_char(input, u))
			return (0);
	}
	else if ((u->c == ' ' || u->c == '\n' || u->c == '\t')
		&& u->quoting_status == UNQUOTED)
	{
		if (!handle_whitespace(input, u))
			return (0);
	}
	else if (u->c == '\'')
		handle_single_quote(u);
	else if (u->c == '\"')
		handle_double_quote(u);
	return (1);
}

int	tokenizer(const char *input, t_token ***tokens)
{
	t_tokenizer_utils	u;

	if (only_whitespaces(input))
		return (0);
	if (!init_tokenizer_utils(&u))
		return (0);
	while (input[u.current])
	{
		u.c = input[u.current];
		if (!route_handler(&u, input))
			return (0);
		u.current++;
	}
	if (u.start != u.current)
	{
		if (!handle_last_token(input, &u))
			return (0);
	}
	*tokens = u.tokens;
	return (1);
}
