/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:06:37 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 01:29:30 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_update_tokens(t_token **result)
{
	t_token	*current;

	current = *result;
	while (current->next)
	{
		if (current->type == WORD && current->space_check == 0
			&& current->next->type == WORD)
			_update_tokens_utils(current);
		else
			current = current->next;
	}
}
