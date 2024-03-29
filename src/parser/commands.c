/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:09:40 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/15 16:21:18 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_pipe(t_token **tokens, t_parser_utils_commands *u)
{
	if (u->redirection)
	{
		u->redirection = NULL;
		u->pipe = tokens[u->i];
	}
	else if (!u->pipe)
	{
		u->pipe = tokens[u->i];
		u->pipe->left = u->command;
		u->command->parent = tokens[u->i];
	}
	else if (u->pipe)
	{
		u->pipe->right = u->command;
		u->command->parent = tokens[u->i];
		u->pipe = tokens[u->i];
	}
}

static void	get_redirection(t_token **tokens, t_parser_utils_commands *u)
{
	int	i;

	i = u->i;
	while (i && tokens[i]->type != PIPE)
	{
		if (token_is_redirection(tokens[i]))
			u->redirection = tokens[i];
		i--;
	}
}

static void	handle_command(t_token **tokens, t_parser_utils_commands *u)
{
	u->command = tokens[u->i];
	if (u->i >= 2 && tokens[u->i - 1]->type == ARGUMENT
		&& token_is_redirection(tokens[u->i - 2]))
	{
		get_redirection(tokens, u);
		u->redirection->left = u->command;
		u->command->parent = u->redirection;
	}
	else
	{
		while (tokens[u->i + 1] && tokens[++u->i]->type != PIPE)
		{
			if (token_is_redirection(tokens[u->i]) && !tokens[u->i]->left)
			{
				u->redirection = tokens[u->i];
				u->redirection->left = u->command;
				u->command->parent = u->redirection;
			}
		}
		if (tokens[u->i] && tokens[u->i]->type == PIPE)
			handle_pipe(tokens, u);
	}
}

t_token	*parse_commands(t_token **tokens)
{
	t_parser_utils_commands	u;

	u.command = NULL;
	u.redirection = NULL;
	u.pipe = NULL;
	u.i = -1;
	while (tokens[++(u.i)])
	{
		if (tokens[u.i]->type == COMMAND)
			handle_command(tokens, &u);
		if (tokens[u.i]->type == PIPE)
			u.pipe = tokens[u.i];
	}
	if (u.pipe && u.command && !u.command->parent)
	{
		u.pipe->right = u.command;
		u.command->parent = u.pipe;
	}
	return (u.command);
}
