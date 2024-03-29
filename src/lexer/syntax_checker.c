/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:28:12 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/15 16:43:46 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	token_is_redirection(t_token *token)
{
	return (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_HEREDOC || token->type == REDIR_APPEND);
}

static bool	pipe_logic_ok(bool *pipe_ok,
							bool *simple_command,
							t_token *token)
{
	if (token->type == COMMAND || token_is_redirection(token))
	{
		*pipe_ok = true;
		*simple_command = true;
	}
	else if (token->type == PIPE)
	{
		if (!*pipe_ok)
			return (false);
		*pipe_ok = false;
	}
	return (true);
}

static char	*check_syntax_errors(t_token **tokens)
{
	int		i;
	bool	pipe_ok;
	bool	simple_command;

	i = -1;
	pipe_ok = false;
	simple_command = false;
	while (tokens[++i])
	{
		if (!pipe_logic_ok(&pipe_ok, &simple_command, tokens[i]))
			return ("|");
		else if (token_is_redirection(tokens[i]) && (!tokens[i + 1] || (tokens[i
						+ 1] && tokens[i + 1]->type != ARGUMENT)))
			return (tokens[i]->value);
	}
	if (simple_command && !pipe_ok)
		return ("|");
	return (NULL);
}

int	syntax_ok(t_token **tokens)
{
	char	*error_string;

	error_string = check_syntax_errors(tokens);
	if (error_string)
	{
		printf("minishell: syntax error near unexpected token `%s\'\n",
			error_string);
		g_mini.exit_status = 2;
		return (0);
	}
	return (1);
}
