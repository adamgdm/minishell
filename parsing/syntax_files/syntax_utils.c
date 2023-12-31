/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:06:23 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/15 06:47:25 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	_syntax_norm(t_token *current)
{
	if (!current->next)
	{
		ft_putstr_fd("Boubou_shell: syntax error near unexpected token `newline'\n", 2);
		g_exit_status = 258;
		return (1);
	}
	if (_check_type(current->next->type) || current->next->type == PIPE)
	{
		ft_putstr_fd("Boubou_shell: syntax error near unexpected token `" , 2);
		ft_putstr_fd(current->next->content, 2);
		ft_putstr_fd("'\n", 2);
		g_exit_status = 258;
		return (1);
	}
	return (0);
}

int	_syntax_norm2(t_token *current)
{
	if (!current->next || current->next->type == PIPE)
	{
		ft_putstr_fd("Boubou_shell: syntax error near unexpected token `|'\n", 2);
		g_exit_status = 258;
		return (1);
	}
	return (0);
}

int	_syntax_norm4(t_token *current)
{
	if (_check_type(current->type))
	{
		if (_syntax_norm(current))
			return (1);
	}
	if (current->type == PIPE)
	{
		if (_syntax_norm2(current))
			return (1);
	}
	return (0);
}

int	_syntax_norm3(t_token *current)
{
	int		i;

	i = 0;
	while (current->content[i])
	{
		if (current->content[0] == '(')
			return (_syntax_norm7(current, i));
		if (current->content[0] == ')')
		{
			ft_putstr_fd("Boubou_shell: syntax error near unexpected token `)'\n", 2);
			g_exit_status = 258;
			return (1);
		}
		if (current->content[i] == '(')
		{
			ft_putstr_fd("Boubou_shell: syntax error near unexpected token `('\n", 2);
			g_exit_status = 258;
			return (1);
		}
		i++;
	}
	return (0);
}
