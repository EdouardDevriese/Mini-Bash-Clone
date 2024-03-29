/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   questionmark.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:14:50 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/05 15:40:03 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	handle_questionmark(t_expander_utils *u)
{
	u->variable_value = ft_itoa(g_mini.exit_status);
	u->before = ft_strndup(u->original, u->i);
	u->after = ft_strdup(u->original + u->i + 2);
	u->result = ft_strjoin(u->before, u->variable_value);
	u->temp = u->result;
	u->result = ft_strjoin(u->temp, u->after);
	free(u->variable_value);
	free(u->before);
	free(u->after);
	free(u->temp);
	u->i += ft_strlen(u->variable_value);
	return (1);
}
