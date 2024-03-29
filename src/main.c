/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:34:46 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/08 10:47:37 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_mini	g_mini;

int	mini_logic(t_env_list *env, char *inp)
{
	int		monitor;
	t_token	**tokens;
	t_token	*ast_head;

	tokens = 0;
	ast_head = 0;
	monitor = tokenizer(inp, &tokens);
	free(inp);
	if (monitor)
		monitor = lexer(tokens);
	if (monitor)
		monitor = parser(tokens, &ast_head);
	if (monitor)
		monitor = expander(tokens, env);
	if (monitor)
		g_mini.exit_status = executor(tokens, ast_head, env);
	free_tokens(tokens);
	return (0);
}

int	loop_main(char *envs[])
{
	t_env_list	*env;
	char		*input;

	env = env_parser(envs);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell: ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		mini_logic(env, input);
	}
	free_env(env);
	rl_clear_history();
	return (0);
}

int	main(int argc, char **argv, char *envs[])
{
	g_mini.exit_status = 0;
	g_mini.in_command = 0;
	g_mini.in_heredoc = 0;
	return (loop_main(envs));
	(void)argc;
	(void)argv;
	(void)envs;
}
