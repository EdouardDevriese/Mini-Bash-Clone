/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:19 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/08 11:08:50 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
• Your shell must implement the following builtins:
DONE◦ echo with option -n
DONE◦ cd with only a relative or absolute path
DONE◦ pwd with no options
DONE◦ export with no options 		#need to have variable list for this
DONE◦ unset with no options			#need to have variable list for this
DONE◦ env with no options or arguments	#need to have variable lsit for this
DONE◦ exit with no options man i dunno
*/
int	unset_builtin(t_token *token, t_env_list *env)
{
	t_env_list	*to_del;
	t_token		*tmp;

	if (syntax_check(token->right))
		return (1);
	tmp = token;
	while (tmp->parent)
		tmp = tmp->parent;
	if (tmp->type == PIPE)
		return (0);
	while (token->right)
	{
		token = token->right;
		set_fd(token);
		to_del = get_env_node(env, token->value);
		if (to_del)
			del_node(&env, to_del);
	}
	return (0);
}

int	exit_builtin(t_token **tokens, t_token *token, t_env_list *env, char **p)
{
	int	atoi;

	if (check_elder_parent(token))
		return (0);
	if (token->right && token->right->right)
	{
		ft_putstr_fd("minishell: exit: Too many arguments\n", 2);
		return (2);
	}
	destroy_deez_nuts(p);
	free_env(env);
	if (token->right && !ft_isnumber(token->right->value))
	{
		ft_putstr_fd("minishell: exit: Non numeric argument\n", 2);
		free_tokens(tokens);
		exit(1);
	}
	if (!token->right)
	{
		free_tokens(tokens);
		exit(0);
	}
	atoi = ft_atoi(token->right->value);
	free_tokens(tokens);
	exit(atoi);
}
//it doesnt matter if im on the left or right side,
//	if i just go up until im at the origin token
//		i can just check that token to see if there were any pipes at all
//this also resets the token to the origin
//	because im assuming the free_tokens command will take that token
//this function will be made to exit only when the exit command is called,
//	dont use it for non command-execution reasons
//exit doesnt do anything if there is a pipe somewhere
//everything else works as expected me thinks
//	TODO: look for syntax errors

int	cd_builtin(t_token *token, t_env_list *env)
{
	char	*path;

	if (token->right && token->right->right)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (token->right)
		path = token->right->value;
	else
	{
		path = get_env_val(env, "HOME");
		if (!path)
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		if (!path)
			return (0);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	return (0);
}

int	pwd_builtin(t_token *token)
{
	char	*retval;

	retval = getcwd(NULL, 0);
	if (!retval)
	{
		return (errno);
	}
	ft_putendl_fd(retval, token->output);
	free(retval);
	return (0);
}

int	env_builtin(t_token *token, t_env_list *env)
{
	if (get_env_node(env, "PATH") == NULL)
	{
		print_error("env", ": No such file or directory");
		return (127);
	}
	while (env)
	{
		if (env->exported == true && env->val)
		{
			ft_putstr_fd(env->var, token->output);
			ft_putchar_fd('=', token->output);
			ft_putendl_fd(env->val, token->output);
		}
		env = env->next;
	}
	return (0);
}
