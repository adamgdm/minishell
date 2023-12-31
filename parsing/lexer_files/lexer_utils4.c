/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:46 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/13 06:02:24 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_token_norm(char *input, t_token **head, int *i)
{
	t_token	*current;

	if (input[*i] && input[*i + 1] == '>')
	{
		current = _create_token(ft_substr(input, *i, 2), REDIRECT_APPEND,
				GENERAL, 1);
		_add_token(head, current);
		*i += 2;
	}
	else
	{
		current = _create_token(ft_substr(input, *i, 1), REDIRECT_OUT, GENERAL,
				1);
		_add_token(head, current);
		(*i)++;
	}
}

void	_token_norm2(char *input, t_token **head, int *i)
{
	t_token	*current;

	if (input[*i] && input[*i + 1] == '<')
	{
		current = _create_token(ft_substr(input, *i, 2), HERE_DOC, GENERAL, 1);
		_add_token(head, current);
		*i += 2;
	}
	else
	{
		current = _create_token(ft_substr(input, *i, 1), REDIRECT_IN, GENERAL,
				1);
		_add_token(head, current);
		(*i)++;
	}
}

void	_join_digit(char **save, char *content, t_data *data, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_fetchvalue(content, data->env);
	if (tmp2)
	{
		tmp = *save;
		*save = ft_strjoin(*save, tmp2);
		free(tmp);
		free(tmp2);
	}
	(*i)++;
}
