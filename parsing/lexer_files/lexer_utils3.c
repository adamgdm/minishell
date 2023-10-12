/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:42 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 01:17:52 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	_lexer_norm(t_token **head, char *input)
{
	printf("Error: unclosed double quote\n");
	g_exit_status = 258;
	_free_all_tokens(head, 1);
	free(input);
	return (0);
}

void	_lexer_norm2(char *input, t_token **head, int *i, int *j)
{
	t_token	*current;

	if ((input[*i + 1] && _it_contains(input[*i + 1])) || !input[*i + 1])
		current = _create_token(ft_substr(input, *j, *i - *j), WORD, IN_DQUOTE,
				1);
	else
		current = _create_token(ft_substr(input, *j, *i - *j), WORD, IN_DQUOTE,
				0);
	_add_token(head, current);
	(*i) = (*i) + 1;
	*j = *i;
}

int	_lexer_norm3(t_token **head, char *input)
{
	printf("Error: unclosed single quote\n");
	g_exit_status = 258;
	_free_all_tokens(head, 1);
	free(input);
	return (0);
}

void	_lexer_norm4(char *input, t_token **head, int *i, int *j)
{
	t_token	*current;

	if ((input[*i + 1] && _it_contains(input[*i + 1])) || !input[*i + 1])
		current = _create_token(ft_substr(input, *j, *i - *j), WORD, IN_QUOTE,
				1);
	else
		current = _create_token(ft_substr(input, *j, *i - *j), WORD, IN_QUOTE,
				0);
	_add_token(head, current);
	(*i) = (*i) + 1;
	*j = *i;
}
