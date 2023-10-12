/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:55 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 01:18:17 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_parser_norm(t_token *current, int *out_file, int *error,
		int *already_printed)
{
	if (*out_file > 2)
		close(*out_file);
	*out_file = open(current->next->content, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (*out_file == -1 && !*already_printed)
	{
		if (ft_strlen(current->next->before_expanded) != 0
			&& ft_strlen(current->next->content) == 0)
		{
			printf("minishell: %s: ambiguous redirect\n",
				current->next->before_expanded);
		}
		else
			printf("minishell: %s: %s\n", current->next->content,
				strerror(errno));
		*error = 1;
		*already_printed = 1;
		g_exit_status = 1;
	}
}

void	_parser_free_norm(t_token *current)
{
	free(current->content);
	current->content = NULL;
	current = current->next;
	free(current->content);
	current->content = NULL;
}

void	_parser_norm2(t_token *current, int *out_file, int *error,
		int *already_printed)
{
	if (*out_file > 2)
		close(*out_file);
	*out_file = open(current->next->content, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (*out_file == -1 && !*already_printed)
	{
		printf("minishell: %s: %s\n", current->next->content, strerror(errno));
		*error = 1;
		*already_printed = 1;
		g_exit_status = 1;
	}
}

void	_parser_norm3(t_token *current, int *in_file, int *error,
		int *already_printed)
{
	if (*in_file > 2)
		close(*in_file);
	*in_file = open(current->next->content, O_RDONLY);
	if (*in_file == -1 && !*already_printed)
	{
		if (ft_strlen(current->next->before_expanded) != 0)
		{
			if (ft_strlen(current->next->content) == 0
				|| _is_there_space_or_tab(current->next->content) == 1)
				printf("minishell: %s: ambiguous redirect\n",
					current->next->before_expanded);
			else
				printf("minishell: %s: No such file or directory\n",
					current->next->content);
		}
		else
			printf("minishell: %s: %s\n", current->next->content,
				strerror(errno));
		*error = 1;
		*already_printed = 1;
		g_exit_status = 1;
	}
}
