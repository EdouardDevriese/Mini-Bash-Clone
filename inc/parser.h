/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:27:25 by wdevries          #+#    #+#             */
/*   Updated: 2024/01/26 10:15:42 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "typedefs.h"
# include <stdio.h>

int		parser(t_token **tokens, t_token **ast_head);
t_token	*parse_pipes(t_token **tokens);
t_token	*parse_redirections(t_token **tokens);
t_token	*parse_commands(t_token **tokens);
t_token	*parse_arguments(t_token **tokens);

#endif
