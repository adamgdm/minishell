/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:40:17 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/14 22:40:18 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_minishell_norm(t_data **g_data, t_commands *commands, char *input,
		t_token **result)
{
	_free_all_tokens(result, 0);
	ft_execute_the_cmd(g_data, commands);
	if (input)
		free(input);
	free_commands(commands);
}

t_commands	*_minishell_norm2(t_token **result, t_data *g_data)
{
	_expander(result, g_data);
	_update_tokens(result);
	return (_parser(result, g_data));
}

int	_minishell_norm3(t_data **g_data)
{
	free_t_data(g_data);
	return (g_exit_status);
}

t_token	*_minishell_norm4(char **input, t_data **g_data)
{
	if (*input && **input)
		add_history(*input);
	if (!*input)
		ft_exit(g_data, NULL);
	return (_lexer(input));
}
