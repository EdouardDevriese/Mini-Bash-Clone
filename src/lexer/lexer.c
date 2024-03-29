/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:05:58 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/02 10:35:16 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	mark_metacharacters(t_token **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i] != NULL)
	{
		if (ft_strcmp(tokens[i]->value, "|") == 0)
			tokens[i]->type = PIPE;
		else if (ft_strcmp(tokens[i]->value, ">") == 0)
			tokens[i]->type = REDIR_OUT;
		else if (ft_strcmp(tokens[i]->value, ">>") == 0)
			tokens[i]->type = REDIR_APPEND;
		else if (ft_strcmp(tokens[i]->value, "<") == 0)
			tokens[i]->type = REDIR_IN;
		else if (ft_strcmp(tokens[i]->value, "<<") == 0)
			tokens[i]->type = REDIR_HEREDOC;
	}
}

static void	set_flags(t_token *token, int *flag_first, int *flag_redirection)
{
	if (token->type == PIPE)
	{
		*flag_first = 1;
		*flag_redirection = 0;
	}
	else
		*flag_redirection = 1;
}

static void	mark_commands_and_arguments(t_token **tokens)
{
	int	flag_first;
	int	flag_redirection;
	int	i;

	flag_first = 1;
	flag_redirection = 0;
	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i]->type != UNDEFINED)
			set_flags(tokens[i], &flag_first, &flag_redirection);
		else
		{
			if (flag_first && !flag_redirection)
			{
				tokens[i]->type = COMMAND;
				flag_first = 0;
			}
			else
			{
				tokens[i]->type = ARGUMENT;
				flag_redirection = 0;
			}
		}
	}
}

int	lexer(t_token **tokens)
{
	mark_metacharacters(tokens);
	mark_commands_and_arguments(tokens);
	return (syntax_ok(tokens));
}
