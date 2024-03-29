/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:30:33 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/15 16:34:29 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//exec pipe
//	RETURN VALUE
// here we start with setting the right side input
// we search for the command
// 	by always going left as the command cant be on the right of a token
// 		except if the token is already a command
// 			(meaning that we are on the right of a pipe)
// set the command of the right side of the syntax tree
// 	to use the read end of the pipe as input
// here we start with setting the output of the left side
// we need to set the output of the right side of that pipe
// 	to be the input of the first pipe
// here we can assume that there are no more pipes to the left,
// meaning we are in a single command, which we search for by going left
// we set the output side of this command to be the write end of the pipe
//	the return value is equal to what the return value of the pipe() command was

void	count_pipes(t_token *token, int *pipes)
{
	if (token->type == PIPE)
		(*pipes)++;
	if (token->left)
		count_pipes(token->left, pipes);
	if (token->right)
		count_pipes(token->right, pipes);
}

int	create_pipes(t_token *token, char ***pipes)
{
	int		pipe_no;
	int		iter;
	char	*num;

	pipe_no = 0;
	count_pipes(token, &pipe_no);
	*pipes = (char **)malloc(sizeof(char *) * pipe_no + 1);
	if (!*pipes)
		return (-1);
	iter = 0;
	while (iter < pipe_no)
	{
		num = ft_itoa(iter);
		(*pipes)[iter] = ft_strjoin("/tmp/deez_nuts_", num);
		free(num);
		iter++;
	}
	(*pipes)[iter] = NULL;
	return (pipe_no);
}

int	count_strs(char **strs)
{
	int	ret;

	ret = 0;
	if (!strs)
		return (0);
	while (strs[ret])
		ret++;
	return (ret);
}

int	open_fds(int filedes[2], char **pipes)
{
	static int	iter = 0;
	int			pipe_no;

	pipe_no = count_strs(pipes);
	filedes[0] = open(pipes[iter], O_RDONLY | O_CREAT | O_TRUNC, 00644);
	filedes[1] = open(pipes[iter], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	iter++;
	if (iter >= pipe_no)
		iter = 0;
	if (filedes[0] == -1 || filedes[1] == -1)
		return (1);
	return (0);
}

//0 is read
//1 is write
int	exec_pipe(t_token *token, char **pipes)
{
	t_token	*tmp;
	int		filedes[2];

	if (open_fds(filedes, pipes))
		return (1);
	tmp = token;
	token = token->right;
	while (token && token->type != COMMAND)
		token = token->left;
	if (token)
		token->input = filedes[0];
	token = tmp;
	token = token->left;
	if (token->type == PIPE)
		token = token->right;
	while (token && token->type != COMMAND)
		token = token->left;
	if (token)
		token->output = filedes[1];
	tmp->input = filedes[0];
	tmp->output = filedes[1];
	return (0);
}
