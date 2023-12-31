/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:06:46 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/15 06:46:07 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	_process_env_value(char *value)
{
	int	i;

	i = 0;
	if (ft_strlen(value) == 0)
		return (0);
	while (value[i] && (value[i] == ' ' || value[i] == '\t'))
		i++;
	while (value[i])
	{
		if (value[i] == ' ' || value[i] == '\t')
		{
			while (value[i] && (value[i] == ' ' || value[i] == '\t'))
				i++;
			if (!value[i])
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	_parser_norm7(t_commands *head, t_vars3 *vars)
{
	free(vars->result_pipe);
	if (vars->commands)
		free(vars->commands);
	free_commands2(head);
	return (1);
}

int	_reset_vars(t_vars3 *vars)
{
	vars->already_printed = 0;
	vars->error = 0;
	vars->in_file = 0;
	vars->out_file = 1;
	return (0);
}
