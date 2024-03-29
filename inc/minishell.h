/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:07:30 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/07 13:07:57 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "typedefs.h"
# include "tokenizer.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "expander.h"
# include "env_parser.h"
# include "signals.h"
# include "../libft/inc/libft.h"

# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

extern t_mini	g_mini;

#endif
