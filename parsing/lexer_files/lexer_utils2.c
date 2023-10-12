/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:38 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 11:35:57 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	_norminette4(char *input, t_vars2 *vars)
{
	if (input[vars->i] == '\"')
	{
		if (!_norminette1(input, &vars->head, &vars->i, &vars->j))
			return (0);
	}
	else if (input[vars->i] == '\'')
	{
		if (!_norminette2(input, &vars->head, &vars->i, &vars->j))
			return (0);
	}
	else
		_norminette3(input, &vars->head, &vars->s, &vars->i);
	return (1);
}
