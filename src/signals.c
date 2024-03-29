/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:20:02 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/12 10:10:56 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	g_mini.exit_status = 130;
	if (!g_mini.in_command && !g_mini.in_heredoc)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
