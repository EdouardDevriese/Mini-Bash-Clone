/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:03:07 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/07 13:12:45 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_dollar_sign(t_expander_utils *u)
{
	if (u->original[u->i + 1] && u->original[u->i + 1] == '?')
		handle_questionmark(u);
	else if (u->original[u->i + 1])
		handle_env_variable(u);
	return (1);
}

int	expand_variables(t_expander_utils *u)
{
	char	c;

	u->i = -1;
	while (u->original[++(u->i)])
	{
		c = u->original[u->i];
		if (c == '$' && (u->quoting_status == UNQUOTED
				|| u->quoting_status == DOUBLE_QUOTED))
		{
			if (!handle_dollar_sign(u))
				return (0);
		}
		else if (c == '\'')
			toggle_single_quote(u);
		else if (c == '\"')
			toggle_double_quote(u);
	}
	return (1);
}

int	remove_quotes(t_expander_utils *u, t_token *token)
{
	char	*no_quotes;
	int		i;
	int		j;

	u->quoting_status = UNQUOTED;
	no_quotes = (char *)malloc(sizeof(char) * ft_strlen(token->value));
	if (!no_quotes)
		return (0);
	i = -1;
	j = -1;
	while (token->value[++i])
	{
		if (token->value[i] == '\'' && u->quoting_status != DOUBLE_QUOTED)
			toggle_single_quote(u);
		else if (token->value[i] == '\"' && u->quoting_status != SINGLE_QUOTED)
			toggle_double_quote(u);
		else
			no_quotes[++j] = token->value[i];
	}
	no_quotes[++j] = '\0';
	free(token->value);
	token->value = no_quotes;
	return (1);
}

int	expander(t_token **tokens, t_env_list *env)
{
	t_expander_utils	u;
	int					i;

	i = -1;
	while (tokens[++i])
	{
		if ((tokens[i]->type == ARGUMENT && !((tokens[i - 1]
						&& ft_strcmp(tokens[i - 1]->value, "<<") == 0)))
			|| tokens[i]->type == COMMAND)
		{
			init_expander_utils(&u, env);
			u.original = tokens[i]->value;
			if (!expand_variables(&u))
				return (0);
			if (u.result)
			{
				free(tokens[i]->value);
				tokens[i]->value = u.result;
			}
			if (!remove_quotes(&u, tokens[i]))
				return (0);
		}
	}
	return (1);
}
