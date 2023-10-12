/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:51 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 01:10:46 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*_lexer(char *input)
{
	t_vars2	vars;

	vars.i = 0;
	vars.j = 0;
	vars.head = NULL;
	vars.s = NULL;
	while (input[vars.i])
	{
		while (input[vars.i] && (input[vars.i] == ' ' || input[vars.i] == '\t'))
			vars.i++;
		if (!input[vars.i])
			break ;
		if (!_it_contains(input[vars.i]))
		{
			vars.j = vars.i;
			while (input[vars.i] && !_it_contains(input[vars.i]))
			{
				if (!_norminette4(input, &vars))
					return (NULL);
			}
		}
		_token_creation(input, &vars.head, &vars.i);
	}
	return (vars.head);
}
