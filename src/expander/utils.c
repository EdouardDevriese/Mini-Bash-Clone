/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:11:13 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/05 15:28:31 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	init_expander_utils(t_expander_utils *u, t_env_list *env)
{
	u->quoting_status = UNQUOTED;
	u->env = env;
	u->original = NULL;
	u->result = NULL;
	u->variable_name = NULL;
	u->variable_value = NULL;
	u->before = NULL;
	u->after = NULL;
	u->temp = NULL;
}

void	toggle_single_quote(t_expander_utils *u)
{
	if (u->quoting_status == SINGLE_QUOTED)
		u->quoting_status = UNQUOTED;
	else if (u->quoting_status == UNQUOTED)
		u->quoting_status = SINGLE_QUOTED;
}

void	toggle_double_quote(t_expander_utils *u)
{
	if (u->quoting_status == DOUBLE_QUOTED)
		u->quoting_status = UNQUOTED;
	else if (u->quoting_status == UNQUOTED)
		u->quoting_status = DOUBLE_QUOTED;
}
