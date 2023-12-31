/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:40:14 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/15 02:42:33 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_minishell_norm5(t_token **result, char *input, int status)
{
	_free_all_tokens(result, status);
	free(input);
}

int	_launch_shell(t_data *g_data)
{
	char		*input;
	t_token		*result;
	t_commands	*commands;
	int			a;

	while (1)
	{
		input = readline("\e[01;32mBoubou_shell> \e[0;37m");
		result = _minishell_norm4(&input, &g_data);
		if (!result)
		{
			free(input);
			continue ;
		}
		a = _syntax_check(&result);
		if (a)
		{
			_minishell_norm5(&result, input, 1);
			if (a == -1)
				return (_minishell_norm3(&g_data));
			continue ;
		}
		commands = _minishell_norm2(&result, g_data);
		if (!commands)
			_minishell_norm5(&result, input, 1);
		else
			_minishell_norm(&g_data, commands, input, &result);
	}
}
