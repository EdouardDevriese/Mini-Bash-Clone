/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:07:05 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/07 13:07:08 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/inc/libft.h"
# include "typedefs.h"
# include <stddef.h>
# include <stdlib.h>

//tokenizer
t_token	*create_token(char *token_value);
int		add_token(t_tokenizer_utils *u, char *token_value);
int		tokenizer(const char *input, t_token ***tokens);
//tokenize_handlers
int		handle_special_char(const char *input, t_tokenizer_utils *u);
int		handle_whitespace(const char *input, t_tokenizer_utils *u);
void	handle_single_quote(t_tokenizer_utils *u);
void	handle_double_quote(t_tokenizer_utils *u);
int		handle_last_token(const char *input, t_tokenizer_utils *u);
//utils
void	free_tokens(t_token **tokens);
int		init_tokenizer_utils(t_tokenizer_utils *u);

#endif
