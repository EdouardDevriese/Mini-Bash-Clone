/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:14 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/06 14:17:07 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	arg_counter(t_token *token)
{
	int	argc;

	argc = 1;
	while (token->right)
	{
		argc++;
		token = token->right;
	}
	return (argc);
}

char	**token_chain_to_array(t_token *token)
{
	char	**result;
	int		argc;
	int		iter;

	argc = arg_counter(token);
	result = (char **)malloc((argc + 1) * (sizeof(char *)));
	if (!result)
		return (0);
	iter = 0;
	while (token)
	{
		result[iter++] = token->value;
		token = token->right;
	}
	result[iter] = NULL;
	return (result);
}

char	*get_env_val(t_env_list *env, char *var)
{
	while (env && ft_strcmp(env->var, var) != 0)
		env = env->next;
	if (!env)
		return (NULL);
	return (env->val);
}
/* return the val of a given var from the env list */

void	free_ast_tree(t_token *token)
{
	if (token->left)
		free_ast_tree(token->left);
	if (token->right)
		free_ast_tree(token->right);
	close(token->input);
	close(token->output);
	free(token->value);
	free(token);
}

int	set_fd(t_token *token)
{
	if (dup2(token->input, STDIN_FILENO) == -1 || dup2(token->output,
			STDOUT_FILENO) == -1)
		return (1);
	return (0);
}
