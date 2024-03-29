/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:33:40 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/12 10:11:20 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//long line arguments wil be given in a linked list of tokens

int	exec_command_builtin(t_token **tokens, t_token *token, t_env_list *env,
		char **p)
{
	if (ft_strncmp(token->value, "echo\0", 5) == 0)
		return (echo_builtin(token));
	else if (ft_strncmp(token->value, "cd\0", 3) == 0)
		return (cd_builtin(token, env));
	else if (ft_strncmp(token->value, "pwd\0", 4) == 0)
		return (pwd_builtin(token));
	else if (ft_strncmp(token->value, "export\0", 7) == 0)
		return (export_builtin(token, env));
	else if (ft_strncmp(token->value, "unset\0", 6) == 0)
		return (unset_builtin(token, env));
	else if (ft_strncmp(token->value, "env\0", 4) == 0)
		return (env_builtin(token, env));
	else if (ft_strncmp(token->value, "exit\0", 5) == 0)
		return (exit_builtin(tokens, token, env, p));
	return (420);
}

int	exec_command(t_token **tokens, t_token *token, t_env_list *env,
		char **pipes)
{
	int	retval;

	retval = exec_command_builtin(tokens, token, env, pipes);
	if (!retval)
		return (0);
	else if (retval != 420)
		return (retval);
	return (exec_command_file(token, env));
}
/*
 *	if no slashes
 * 		1. attempt to execute as is,
			ig to see if that executable just exists in working directory
 * 		2. check if built in
 * 		3. look in $path
 * 	if any of prev = succes or contains slashes
 * 		execute program is seperate execution env (fork)
 *
 * 	im gonna reduce this to
 * 		1. execute as is
 * 		2. try execute as builtin
 * 		3. try execute from $path
 *
 *		
*/

int	execute(t_token **tokens, t_token *token, t_env_list *env, char **pipes)
{
	if (token->type == PIPE)
		return (exec_pipe(token, pipes));
	else if (token->type == REDIR_IN)
		return (exec_redir_in(token));
	else if (token->type == REDIR_OUT)
		return (exec_redir_out(token));
	else if (token->type == REDIR_HEREDOC)
		return (exec_redir_heredoc(token));
	else if (token->type == REDIR_APPEND)
		return (exec_redir_append(token));
	else if (token->type == COMMAND)
		return (exec_command(tokens, token, env, pipes));
	return (1);
}

int	exec_token(t_token **tokens, t_token *token, t_env_list *env, char **pipes)
{
	int	retval;

	retval = 0;
	if (token->value[0])
		retval = execute(tokens, token, env, pipes);
	if (token->output != 1 && token->type != PIPE && token->type != REDIR_APPEND
		&& token->type != REDIR_OUT)
		close(token->output);
	if (retval)
		return (retval);
	if (token->left && token->left->type != ARGUMENT)
		retval = exec_token(tokens, token->left, env, pipes);
	if (retval)
		return (retval);
	if (token->right && token->right->type != ARGUMENT)
		retval = exec_token(tokens, token->right, env, pipes);
	return (retval);
}

int	executor(t_token **tokens, t_token *token, t_env_list *env)
{
	int		retval;
	char	**pipes;
	pid_t	child;

	retval = 0;
	pipes = NULL;
	if (set_here_filedes(token))
		return (1);
	g_mini.in_heredoc = 1;
	child = fork();
	if (child == 0)
		exec_heredocs(token, env);
	waitpid(child, &retval, 0);
	g_mini.in_heredoc = 0;
	check_child(&retval);
	if (retval)
		return (retval);
	create_pipes(token, &pipes);
	retval = exec_token(tokens, token, env, pipes);
	destroy_deez_nuts(pipes);
	return (retval);
}
