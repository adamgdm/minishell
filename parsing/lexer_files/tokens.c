/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:06:33 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 01:18:02 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*_create_token(char *value, enum e_token type, enum e_state state,
		int space_check)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = value;
	token->type = type;
	token->state = state;
	token->space_check = space_check;
	token->before_expanded = ft_strdup("");
	token->next = NULL;
	return (token);
}

void	_add_token(t_token **head, t_token *new)
{
	t_token	*current;

	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	_free_all_tokens(t_token **head, int check)
{
	t_token	*current;
	t_token	*tmp;
	int		i;

	current = *head;
	i = 1;
	while (current)
	{
		tmp = current;
		current = current->next;
		if (check == 1)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		free(tmp->before_expanded);
		free(tmp);
		i++;
	}
	*head = NULL;
}
