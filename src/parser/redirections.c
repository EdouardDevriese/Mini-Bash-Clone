/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:24:44 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/02 11:09:28 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_redirection(t_token *token, t_parser_utils_redir *u)
{
	if (u->last_redirection)
	{
		token->parent = u->last_redirection;
		u->last_redirection->left = token;
	}
	else
		u->first_redirection = token;
	u->last_redirection = token;
}

static void	handle_pipe(t_token *token, t_parser_utils_redir *u)
{
	if (u->pipe && u->first_redirection)
	{
		u->pipe->right = u->first_redirection;
		u->first_redirection->parent = u->pipe;
	}
	else if (!u->pipe && u->first_redirection)
	{
		u->pipe = token;
		u->pipe->left = u->first_redirection;
		u->first_redirection->parent = u->pipe;
	}
	u->pipe = token;
	u->last_redirection = NULL;
	u->first_redirection = NULL;
}

t_token	*parse_redirections(t_token **tokens)
{
	t_parser_utils_redir	u;
	int						i;

	u.last_redirection = NULL;
	u.first_redirection = NULL;
	u.pipe = NULL;
	i = -1;
	while (tokens[++i])
	{
		if (token_is_redirection(tokens[i]))
			handle_redirection(tokens[i], &u);
		else if (tokens[i]->type == PIPE)
			handle_pipe(tokens[i], &u);
	}
	if (u.first_redirection && u.pipe)
	{
		u.pipe->right = u.first_redirection;
		u.first_redirection->parent = u.pipe;
	}
	return (u.first_redirection);
}
