/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:08:06 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/29 13:08:36 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env_node(t_env_list *env)
{
	if (!env)
		return ;
	if (env->val)
		free(env->val);
	if (env->var)
		free(env->var);
	free(env);
}

void	free_env(t_env_list *env)
{
	t_env_list	*tmp;

	while (env)
	{
		tmp = env->next;
		free_env_node(env);
		env = tmp;
	}
}

t_env_list	*get_env_node(t_env_list *head, char *var)
{
	while (head && ft_strcmp(head->var, var))
		head = head->next;
	return (head);
}
/* searches through env_list head until either head->var is equal to var
 * or until head == NULL
 * either way it return head
 * 		which will either be null or the found node
 */
