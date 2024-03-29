/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:23:49 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/08 11:15:14 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_child(t_token *token, char *cmd_path, char **args)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (dup2(token->input, STDIN_FILENO) == -1 || dup2(token->output,
			STDOUT_FILENO) == -1)
		exit(errno);
	execve(cmd_path, args, NULL);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token->value, 2);
	ft_putstr_fd(": no such file or directory\n", 2);
	exit(127);
}

int	check_child(int *child_status)
{
	if (WIFEXITED(*child_status))
	{
		*child_status = WEXITSTATUS(*child_status);
		if (*child_status != 0)
			return (1);
	}
	return (0);
}

int	get_args(t_token *token, t_env_list *env, char **cmd_path, char ***args)
{
	t_token	token_tmp;

	if (ft_strchr(token->value, '/') == NULL)
		*cmd_path = get_full_cmd_path(token->value, env);
	else
		*cmd_path = ft_strdup(token->value);
	if (!*cmd_path)
		return (1);
	token_tmp.value = *cmd_path;
	token_tmp.right = token->right;
	*args = token_chain_to_array(&token_tmp);
	return (0);
}

int	create_child(t_token *token, char **args, char *cmd_path)
{
	int		status;
	pid_t	child;

	g_mini.in_command = 1;
	child = fork();
	status = 0;
	if (child == 0)
		exec_child(token, cmd_path, args);
	else if (child > 0)
	{
		waitpid(child, &status, 0);
		g_mini.in_command = 0;
		free(cmd_path);
		free(args);
		check_child(&status);
	}
	return (status);
}

int	exec_command_file(t_token *token, t_env_list *env)
{
	char	*cmd_path;
	int		status;
	char	**args;

	args = 0;
	get_args(token, env, &cmd_path, &args);
	status = 127;
	if (cmd_path)
	{
		if (is_dir(cmd_path))
		{
			print_error(token->value, ": Is a directory");
			status = 126;
			free(cmd_path);
			free(args);
		}
		else
			status = create_child(token, args, cmd_path);
	}
	else
		ft_printf("%s: command not found\n", token->value);
	return (status);
}
/*                                                            
* check if the given token->value has a slash,
if so we must use that as the command as is                                     
   
* else we will try to find a suitable path in the $path
* 	should it (and $path) exist                                            
*/
/*                                                            
 * these will be our execve arguments                         
 * these start from the command itself
 * 	cuz we need that       
 * TMP_FIX: create tmp token with full path
 * 	to replace the actual command token
 *			token doesnt need freeing ig
 */
