/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:04:51 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 01:18:23 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_do_norm(t_token *current, t_vars3 *vars)
{
	_parser_norm(current, &vars->out_file, &vars->error,
		&vars->already_printed);
	_parser_free_norm(current);
}

int	_do_norm2(t_token *current)
{
	if (current->type == WORD && (ft_strchr(current->content, ')')
			|| ft_strchr(current->content, '(')) && !ft_strchr(current->content,
			'\\'))
		return (1);
	return (0);
}

void	_do_norm3(t_token *current, t_vars3 *vars, t_data *data)
{
	if (current->type == REDIRECT_IN)
	{
		_parser_norm3(current, &vars->in_file, &vars->error,
			&vars->already_printed);
		_parser_free_norm(current);
	}
	else if (current->type == HERE_DOC)
	{
		_parser_norm4(current, &vars->in_file, data);
		_parser_free_norm(current);
	}
}
