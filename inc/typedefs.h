/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:07:15 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/07 13:07:17 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include <stdbool.h>

typedef struct s_mini
{
	int					exit_status;
	int					in_command;
	int					in_heredoc;
}						t_mini;

typedef enum e_token_type
{
	UNDEFINED,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND,
	COMMAND,
	ARGUMENT
}						t_token_type;

typedef enum e_quoting_status
{
	UNQUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
}						t_quoting_status;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*left;
	struct s_token		*right;
	struct s_token		*parent;
	short				input;
	short				output;
}						t_token;

typedef struct s_env_list
{
	bool				exported;
	char				*var;
	char				*val;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_tokenizer_utils
{
	int					size;
	int					capacity;
	int					new_capacity;
	int					start;
	int					current;
	char				c;
	t_quoting_status	quoting_status;
	t_token				**tokens;
	t_token				**new_tokens;
}						t_tokenizer_utils;

typedef struct s_parser_utils_redir
{
	t_token				*last_redirection;
	t_token				*first_redirection;
	t_token				*pipe;
	int					i;
}						t_parser_utils_redir;

typedef struct s_parser_utils_commands
{
	t_token				*command;
	t_token				*redirection;
	t_token				*pipe;
	int					i;
}						t_parser_utils_commands;

typedef struct s_expander_utils
{
	t_quoting_status	quoting_status;
	t_env_list			*env;
	int					exit_status;
	int					i;
	char				*original;
	char				*result;
	char				*variable_name;
	char				*variable_value;
	char				*before;
	char				*after;
	char				*temp;
}						t_expander_utils;

#endif
