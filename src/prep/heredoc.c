/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:06:54 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/08 11:18:47 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const char	*remove_quotes_heredoc(t_token *token, t_env_list *env)
{
	t_expander_utils	u;

	init_expander_utils(&u, env);
	u.original = token->value;
	remove_quotes(&u, token);
	return (token->value);
}

static char	*expand_variables_heredoc(char *str, t_env_list *env)
{
	t_expander_utils	u;

	init_expander_utils(&u, env);
	u.original = str;
	expand_variables(&u);
	if (u.result)
		return (u.result);
	else
		return (u.original);
}

int	heredoc_prep(t_token *token, t_env_list *env, const char **del, bool *exp)
{
	*exp = false;
	if (!ft_strchr((const char *)token->right->value, '\"')
		&& !ft_strchr((const char *)token->right->value, '\''))
		*exp = true;
	else
		remove_quotes_heredoc(token->right, env);
	*del = (const char *)token->right->value;
	return (0);
}

int	read_heredoc(t_token *token, t_env_list *env)
{
	char		*str;
	const char	*deliminator;
	bool		expand_variables;

	heredoc_prep(token, env, &deliminator, &expand_variables);
	str = readline(">");
	while (ft_strcmp(str, deliminator) != 0)
	{
		if (!str)
		{
			ft_putstr_fd(" minishell: warning: here-document delimited by end-\
of-file (wanted `", 2);
			ft_putstr_fd((char *)deliminator, 2);
			ft_putendl_fd("')", 2);
			break ;
		}
		if (expand_variables)
			str = expand_variables_heredoc(str, env);
		ft_putendl_fd(str, token->output);
		if (expand_variables)
			free(str);
		str = readline(">");
	}
	ft_putchar_fd('\0', token->output);
	close(token->output);
	return (0);
}

int	exec_heredocs(t_token *head, t_env_list *env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	if (head->left)
		exec_heredocs(head->left, env);
	if (head->right)
		exec_heredocs(head->right, env);
	if (head->type == REDIR_HEREDOC)
	{
		read_heredoc(head, env);
	}
	if (!head->parent)
		exit (0);
	return (0);
}
