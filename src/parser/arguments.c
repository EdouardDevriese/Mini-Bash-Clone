/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:34:57 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/15 16:57:13 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	link_redirection_arguments(t_token **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (token_is_redirection(tokens[i]) && tokens[i + 1] && tokens[i
				+ 1]->type == ARGUMENT)
		{
			tokens[i]->right = tokens[i + 1];
			tokens[i + 1]->parent = tokens[i];
		}
	}
}

static void	link_command_arguments(t_token **tokens)
{
	int		i;
	t_token	*parent;

	i = -1;
	while (tokens[++i])
	{
		if (tokens[i]->type == COMMAND)
		{
			parent = tokens[i];
			while (tokens[i + 1] && tokens[++i]->type != PIPE)
			{
				if (tokens[i]->type == ARGUMENT && !tokens[i]->parent)
				{
					parent->right = tokens[i];
					tokens[i]->parent = parent;
					parent = tokens[i];
				}
			}
		}
	}
}

t_token	*parse_arguments(t_token **tokens)
{
	if (tokens[0] && !tokens[1] && tokens[0]->type == ARGUMENT)
		return (tokens[0]);
	link_redirection_arguments(tokens);
	link_command_arguments(tokens);
	return (NULL);
}
