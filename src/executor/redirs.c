/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:53:09 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/06 10:31:18 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_redir_in(t_token *token)
{
	char	*file;
	t_token	*redir;
	int		fd;

	redir = token;
	file = token->right->value;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(file, ": No such file or directory"));
	while (token && token->type != COMMAND)
		token = token->left;
	if (!token)
		return (0);
	token->input = fd;
	redir->input = token->input;
	return (0);
}

int	exec_redir_out(t_token *token)
{
	char	*file;
	t_token	*redir;
	int		fd;

	redir = token;
	file = token->right->value;
	if (is_dir(file))
		return (print_error(file, ": Is a directory"));
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fd == -1)
		return (1);
	while (token && token->type != COMMAND)
		token = token->left;
	if (!token)
		return (0);
	token->output = fd;
	redir->output = token->output;
	return (0);
}

int	exec_redir_append(t_token *token)
{
	char	*file;
	t_token	*redir;
	int		fd;

	redir = token;
	file = token->right->value;
	if (is_dir(file))
		return (print_error(file, ": Is a directory"));
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 00644);
	if (fd == -1)
		return (-1);
	while (token && token->type != COMMAND)
		token = token->left;
	if (!token)
		return (0);
	token->output = fd;
	redir->output = token->output;
	return (0);
}

int	exec_redir_heredoc(t_token *token)
{
	t_token	*redir;

	redir = token;
	while (token && token->type != COMMAND)
		token = token->left;
	if (!token)
		return (0);
	token->input = redir->input;
	return (0);
}
/*
 *	I think heredoc should be done before executing
 *	Reason : 
 *		if you run "cat << EOF > outfile"
 *		according to execution rules,
			outfile should be generated before the heredoc is initiated
 *		However
 *		If you cancel heredoc with control
			+ c then you can see that the outfile is in fact not generated yet
 *
 *		if heredoc happens in a previous step,
			it would be logical to store the fd
				from which i need to reed inside of the heredoc token,
			so i can just copy that into the correct token
 */
