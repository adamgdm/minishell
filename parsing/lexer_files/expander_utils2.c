/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 06:12:24 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/13 06:12:47 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_expander_norm(t_token **head)
{
	*head = (*head)->next->next;
	while (*head && (*head)->space_check == 0)
		*head = (*head)->next;
	if (*head && (*head)->type != HERE_DOC)
		*head = (*head)->next;
}

void	_expander_norm2(t_token **head, t_data *data)
{
	char	*tmp;

	_update_before_expanded(head);
	tmp = _expand_word(*head, data);
	if ((*head)->state == GENERAL)
	{
		(*head)->content = ft_strtrim(tmp, " \t");
		free(tmp);
	}
	else
		(*head)->content = tmp;
}
