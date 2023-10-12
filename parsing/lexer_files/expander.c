/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:23 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 01:05:24 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*_expand_word(char *content, t_data *data)
{
	t_vars	vars;

	vars.i = 0;
	vars.j = 0;
	vars.k = 0;
	vars.save = ft_strdup("");
	while (content[vars.i])
	{
		if (content[vars.i] == '$')
			_norminette(&vars.save, content, data, &vars);
		else if (content[vars.i] && content[vars.i] != '$')
		{
			vars.save = _append(vars.save, content[vars.i]);
			vars.i++;
			vars.j = vars.i;
		}
	}
	free(content);
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
	char	*tmp;

	head = *result;
	while (head)
	{
		if (head->type == HERE_DOC)
		{
			head = head->next->next;
			while (head && head->space_check == 0)
				head = head->next;
			if (head && head->type != HERE_DOC)
				head = head->next;
			continue ;
		}
		if (_contains_dollar(head->content) && (head->state == GENERAL
				|| head->state == IN_DQUOTE))
		{
			_update_before_expanded(&head);
			tmp = _expand_word(head->content, data);
			head->content = ft_strtrim(tmp, " \t");
			free(tmp);
		}
		head = head->next;
	}
}
