/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:41:24 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/18 13:23:15 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*parse_pipes(t_token **tokens)
{
	t_token	*pipe;
	int		i;

	pipe = NULL;
	i = -1;
	while (tokens[++i])
	{
		if (tokens[i]->type == PIPE)
		{
			if (pipe)
			{
				tokens[i]->left = pipe;
				pipe->parent = tokens[i];
			}
			pipe = tokens[i];
		}
	}
	return (pipe);
}
