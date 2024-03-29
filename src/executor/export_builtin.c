/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:28:01 by vdenisse          #+#    #+#             */
/*   Updated: 2024/01/29 13:39:55 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_var_and_val(char **var, char **val, t_token *token)
{
	int	type;

	type = 2;
	if (!token)
		return (0);
	*val = ft_strchr(token->value, '=');
	if (!*val)
	{
		*var = ft_strdup(token->value);
		return (1);
	}
	if (*(*val - 1) == '+')
		type = 3;
	if (type == 3)
		*var = ft_substr(token->value, 0, *val - token->value - 1);
	else
		*var = ft_substr(token->value, 0, *val - token->value);
	(*val)++;
	*val = ft_strdup(*val);
	return (type);
}
// export type = 0
// default export var=val type = 2
// // export var type = 1
// // export var+=val type = 3

int	export_builtin(t_token *token, t_env_list *env)
{
	char		*val;
	char		*var;
	int			type;
	t_env_list	*node;

	if (check_elder_parent(token))
		return (0);
	if (syntax_check(token->right))
		return (1);
	type = get_var_and_val(&var, &val, token->right);
	if (type == 0)
		return (print_export(token, env));
	node = get_env_node(env, var);
	if (type == 1)
		handle_1(env, node, var);
	else if (type == 2 || !node)
		handle_2(env, node, var, val);
	else
		handle_3(node, val);
	if (var)
		free(var);
	if (val)
		free(val);
	return (0);
}
//new plan of action
//	first things first check the syntax
//
//could add a export boolean parameter,
//		that way i could use export for set also
//
//all different cases
//	if elder parent == "|"
//		do nothing
//	if = is preset
//		if  + is before =
//			set append = true
//		if "var" exists
//			overwrite or append var with new val
//		else
//			create new env_list node
//
//

//check if no args
//try to export for each arg token,
//for each token
// 1.look for = sign
//	if = is found
//		create new variable with corresponding values and set export=true
//	if = is ! found
//		find env variable by name value and set corresponding export=true
//	TODO: look for syntax errors
