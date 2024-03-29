/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:25:56 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/07 12:26:28 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	set_single_here_filedes(t_token *token)
{
	int	filedes[2];

	if (pipe(filedes) == -1)
		return (1);
	token->input = filedes[0];
	token->output = filedes[1];
	return (0);
}

int	set_here_filedes(t_token *token)
{
	if (token->type == REDIR_HEREDOC)
		if (set_single_here_filedes(token))
			return (1);
	if (token->right)
		if (set_here_filedes(token->right))
			return (1);
	if (token->left)
		if (set_here_filedes(token->left))
			return (1);
	return (0);
}
