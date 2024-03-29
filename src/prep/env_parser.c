/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:05:51 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/29 13:10:27 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_list	*del_node(t_env_list **head, t_env_list *to_del)
{
	t_env_list	*tmp;
	t_env_list	*prev;

	if (!to_del || !head)
		return (NULL);
	tmp = *head;
	if (to_del == tmp)
	{
		*head = (*head)->next;
		free_env_node(tmp);
	}
	else
	{
		while (tmp != to_del)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp != to_del)
			return (NULL);
		prev->next = tmp->next;
		free_env_node(tmp);
	}
	return (*head);
}
/*
 * delete to_del from env_list
 * if to_del is head then set head to be next first node
 */

t_env_list	*env_node_con(char *var, char *val, bool exported)
{
	t_env_list	*new;

	new = (t_env_list *)malloc((1) * (sizeof(t_env_list)));
	if (!new)
		return (NULL);
	new->val = ft_strdup(val);
	new->var = ft_strdup(var);
	new->next = NULL;
	new->exported = exported;
	if (!new->var)
	{
		free_env_node(new);
		return (NULL);
	}
	return (new);
}

t_env_list	*env_line_parser(char *env_line)
{
	t_env_list	*new;
	char		*val;
	char		*var;
	short		index;

	val = ft_strchr(env_line, '=');
	if (!val)
		return (NULL);
	index = val - env_line;
	val++;
	var = ft_substr(env_line, 0, index);
	new = env_node_con(var, val, true);
	free(var);
	return (new);
}

void	env_add_back(t_env_list **head, t_env_list *to_add)
{
	t_env_list	*tmp;

	if (!to_add)
		return ;
	if (!*head)
	{
		*head = to_add;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = to_add;
	return ;
}
/* similar to ft_lstadd_back
 */

t_env_list	*env_parser(char *env[])
{
	t_env_list	*head;
	int			iter;

	iter = 0;
	head = NULL;
	while (env[iter])
	{
		env_add_back(&head, env_line_parser(env[iter]));
		iter++;
	}
	return (head);
}
/*
 * parse env into t_env_list linked list structure
 * still need to check this for error handling
 */
