/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:32:06 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/02 12:32:39 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	if (tokens == NULL)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->output != 1)
			close(tokens[i]->output);
		if (tokens[i]->input != 0)
			close(tokens[i]->input);
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	init_tokenizer_utils(t_tokenizer_utils *u)
{
	u->size = 0;
	u->new_capacity = 0;
	u->capacity = 10;
	u->start = 0;
	u->current = 0;
	u->quoting_status = UNQUOTED;
	u->new_tokens = NULL;
	u->tokens = (t_token **)malloc(u->capacity * sizeof(t_token *));
	if (!u->tokens)
		return (0);
	return (1);
}
