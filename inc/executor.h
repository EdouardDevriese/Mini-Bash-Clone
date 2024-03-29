/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:30:16 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/08 11:44:27 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

# define NOT_EXECUTABLE 129

//this token is the first ARG token
//converts the chain of token ARGS to a single array
//only the char ** needs freeing, as all the char
//	* are pointers to the token values
char	**token_chain_to_array(t_token *token);

//this token is the cmd token
int		exec_command_file(t_token *token, t_env_list *env);
int		check_child(int *child_status);

int		executor(t_token **tokens, t_token *token, t_env_list *env);

char	*get_full_cmd_path(char *cmd, t_env_list *env);

int		exec_token(t_token **tokens, t_token *token, t_env_list *env,
			char **pipes);

int		env_builtin(t_token *token, t_env_list *env);
int		cd_builtin(t_token *token, t_env_list *env);
int		pwd_builtin(t_token *token);
int		echo_builtin(t_token *token);
int		exit_builtin(t_token **tokens, t_token *token, t_env_list *env,
			char **p);
int		unset_builtin(t_token *token, t_env_list *env);
int		export_builtin(t_token *token, t_env_list *env);

int		exec_pipe(t_token *token, char **pipes);
int		create_pipes(t_token *token, char ***pipes);
int		destroy_deez_nuts(char **pipes);

int		exec_redir_in(t_token *token);
int		exec_redir_out(t_token *token);
int		exec_redir_append(t_token *token);
int		exec_redir_heredoc(t_token *token);

char	*get_env_val(t_env_list *env, char *var);
void	free_ast_tree(t_token *token);
bool	syntax_check(t_token *token);
int		set_fd(t_token *token);

bool	check_elder_parent(t_token *token);
bool	is_dir(const char *str);
int		print_error(char *file, char *error);
int		ft_isnumber(char *str);

int		handle_1(t_env_list *env, t_env_list *node, char *var);
int		handle_2(t_env_list *env, t_env_list *node, char *var, char *val);
int		handle_3(t_env_list *node, char *val);
int		print_export(t_token *token, t_env_list *env);

#endif
