/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdevries <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:18:29 by wdevries          #+#    #+#             */
/*   Updated: 2024/02/02 12:30:07 by wdevries         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*get_variable_name(t_expander_utils *u)
{
	int	start;
	int	len;

	start = u->i + 1;
	len = 0;
	if (!(ft_isalpha(u->original[start]) || u->original[start] == '_'))
		return (NULL);
	while (u->original[start + len] && (ft_isalnum(u->original[start + len])
			|| u->original[start + len] == '_'))
		len++;
	return (ft_strndup(u->original + start, len));
}

static char	*get_variable_value(t_expander_utils *u, char *variable_name)
{
	t_env_list	*current;

	current = u->env;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, variable_name) == 0)
		{
			if (current->val)
				return (ft_strdup(current->val));
			else
				return (ft_strdup(""));
		}
		current = current->next;
	}
	return (ft_strdup(""));
}

static char	*get_variable(t_expander_utils *u)
{
	u->variable_name = get_variable_name(u);
	if (!u->variable_name)
		return (NULL);
	return (get_variable_value(u, u->variable_name));
}

int	handle_env_variable(t_expander_utils *u)
{
	u->variable_value = get_variable(u);
	if (u->variable_value)
	{
		u->before = ft_strndup(u->original, u->i);
		u->after = (ft_strdup(u->original + u->i + ft_strlen(u->variable_name)
					+ 1));
		u->result = ft_strjoin(u->before, u->variable_value);
		u->temp = u->result;
		u->result = ft_strjoin(u->temp, u->after);
		u->i += ft_strlen(u->variable_value - 1);
	}
	free(u->before);
	free(u->after);
	free(u->temp);
	free(u->variable_value);
	free(u->variable_name);
	return (1);
}
