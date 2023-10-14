/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:23 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/14 08:18:03 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	_contains_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*_expand_word(t_token *head, t_data *data)
{
	t_vars	vars;

	vars.i = 0;
	vars.j = 0;
	vars.k = 0;
	vars.save = ft_strdup("");
	while (head->content[vars.i])
	{
		if (head->content[vars.i] == '$')
			_norminette(&vars.save, head, data, &vars);
		else if (head->content[vars.i] && head->content[vars.i] != '$')
		{
			vars.save = _append(vars.save, head->content[vars.i]);
			vars.i++;
			vars.j = vars.i;
		}
	}
	free(head->content);
	return (vars.save);
}

void	_update_before_expanded(t_token **head)
{
	if (ft_strlen((*head)->content) != 1)
	{
		free((*head)->before_expanded);
		(*head)->before_expanded = ft_strdup((*head)->content);
	}
}

void	_expander(t_token **result, t_data *data)
{
	t_token	*head;

	head = *result;
	while (head)
	{
		if (head->type == HERE_DOC)
		{
			_expander_norm(&head);
			continue ;
		}
		if (_contains_dollar(head->content) && (head->state == GENERAL
				|| head->state == IN_DQUOTE))
		{
			_expander_norm2(&head, data);
		}
		head = head->next;
	}
}
