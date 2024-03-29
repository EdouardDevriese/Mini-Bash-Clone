/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:16:24 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/01 10:35:36 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	check_single_token(t_token *token)
{
	int	i;

	if (!token || !token->value)
		return (false);
	if (token->value[0] != '-')
		return (false);
	if (!token->value[1])
		return (false);
	i = 0;
	while (token->value[++i] && token->value[i] == 'n')
		;
	if (!token->value[i])
		return (true);
	return (false);
}

static int	echo_check_option_v2(t_token **token, bool *option)
{
	bool	cont;
	t_token	*tmp;

	cont = true;
	tmp = *token;
	while (cont)
	{
		tmp = tmp->right;
		cont = check_single_token(tmp);
		if (!(*option) && cont)
			*option = true;
	}
	*token = tmp;
	return (0);
}

// loop over every token
// stop once a non -n or -nnnn combo is found
// advance

int	echo_builtin(t_token *token)
{
	bool	option;
	char	**token_chain;
	int		iter;
	t_token	*echo;

	echo = token;
	option = false;
	echo_check_option_v2(&token, &option);
	if (token)
	{
		token_chain = NULL;
		token_chain = token_chain_to_array(token);
		iter = 0;
		while (token_chain && token_chain[iter])
		{
			ft_putstr_fd(token_chain[iter], echo->output);
			if (token_chain[++iter])
				ft_putchar_fd(' ', echo->output);
		}
		free(token_chain);
	}
	if (!option)
		write(echo->output, "\n", 1);
	return (0);
}
//TODO token_chain_to_array can fail
//TODO options can be formatted as such "-nnnnn"
//	but wont do anything if there is another option present eg:"-nnnp"
//still need to add the optional option check for -n
//DONE need to put spaces in between all the arguments
//except when there is no space but quotes
