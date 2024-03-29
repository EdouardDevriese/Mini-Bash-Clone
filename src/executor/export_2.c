/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:38:31 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/29 13:39:46 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_export(t_token *token, t_env_list *env)
{
	while (env)
	{
		if (env->exported == true)
		{
			ft_putstr_fd("declare -x ", token->output);
			ft_putstr_fd(env->var, token->output);
			if (env->val != NULL)
			{
				ft_putchar_fd('=', token->output);
				ft_putchar_fd('"', token->output);
				ft_putstr_fd(env->val, token->output);
				ft_putchar_fd('"', token->output);
			}
			ft_putchar_fd('\n', token->output);
		}
		env = env->next;
	}
	return (0);
}

/*
 * tings to shek
 *		START with beeg or smoll letta or with undascore
 *	after first
 *		can be any letta, numba, undascore
 *
 */
int	handle_3(t_env_list *node, char *val)
{
	char	*tmp;

	tmp = ft_strjoin(node->val, val);
	free(node->val);
	node->val = tmp;
	return (0);
}

int	handle_2(t_env_list *env, t_env_list *node, char *var, char *val)
{
	if (node)
	{
		if (node->val)
			free(node->val);
		if (node->var)
			free(node->var);
		node->var = ft_strdup(var);
		node->val = ft_strdup(val);
	}
	else
		env_add_back(&env, env_node_con(var, val, 1));
	return (0);
}

int	handle_1(t_env_list *env, t_env_list *node, char *var)
{
	if (node)
		node->exported = true;
	else
		env_add_back(&env, env_node_con(var, NULL, 1));
	return (0);
}
