/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:33 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 01:10:33 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_norminette1(char *input, t_token **head, int *i, int *j)
{
	t_token	*current;

	(*i) = (*i) + 1;
	*j = *i;
	while (input[*i] && input[*i] != '\"')
		(*i) = (*i) + 1;
	if (!input[*i])
		return (_lexer_norm(head, input));
	else if (input[*i] == '\"')
		_lexer_norm2(input, head, i, j);
	return (1);
}

int	_norminette2(char *input, t_token **head, int *i, int *j)
{
	t_token	*current;

	(*i) = (*i) + 1;
	*j = *i;
	while (input[*i] && input[*i] != '\'')
		(*i) = (*i) + 1;
	if (!input[*i])
		return (_lexer_norm3(head, input));
	else if (input[*i] == '\'')
		_lexer_norm4(input, head, i, j);
	return (1);
}

void	_norminette3(char *input, t_token **head, char **save, int *i)
{
	t_token	*current;

	*save = _append(*save, input[*i]);
	(*i) = (*i) + 1;
	if (_it_contains(input[*i]) || !input[*i] || input[*i] == '\"'
		|| input[*i] == '\'')
	{
		if (input[*i] == '"' || input[*i] == '\'')
			current = _create_token(*save, WORD, GENERAL, 0);
		else
			current = _create_token(*save, WORD, GENERAL, 1);
		_add_token(head, current);
		*save = NULL;
	}
}

void	_token_creation(char *input, t_token **head, int *i)
{
	t_token	*current;

	if (input[*i] == '|')
	{
		current = _create_token(ft_substr(input, *i, 1), PIPE, GENERAL, 1);
		_add_token(head, current);
		(*i)++;
	}
	else if (input[*i] == '<')
		_token_norm2(input, head, i);
	else if (input[*i] == '>')
		_token_norm(input, head, i);
}
