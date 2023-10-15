/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:15:55 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 00:23:05 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_last_node(t_env **head)
{
	t_env	*current;
	t_env	*previous;

	if (*head == NULL)
		return ;
	if ((*head)->next == NULL)
	{
		free((*head)->str);
		free(*head);
		*head = NULL;
		return ;
	}
	current = *head;
	previous = NULL;
	while (current->next != NULL)
	{
		previous = current;
		current = current->next;
	}
	free(current->str);
	free(current);
	previous->next = NULL;
}

void	add_last_node(t_env **head, const char *str)
{
	t_env	*new_node;
	t_env	*current;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		perror("Memory allocation failed");
		return ;
	}
	new_node->str = ft_strdup(str);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_node;
}

void	add_bln_norminette(t_env **head, char *str)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	new_node->str = ft_strdup(str);
	new_node->next = *head;
	*head = new_node;
}

void	add_before_last_node(t_env **head, char *str)
{
	t_env	*new_node;
	t_env	*current;

	if (*head == NULL)
	{
		add_last_node(head, str);
		return ;
	}
	if ((*head)->next == NULL)
	{
		add_bln_norminette(head, str);
		return ;
	}
	current = *head;
	while (current->next->next != NULL)
		current = current->next;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		perror("Memory allocation failed");
		return ;
	}
	new_node->str = ft_strdup(str);
	new_node->next = current->next;
	current->next = new_node;
}

void	ft_deletethenode(t_env **head, char *target)
{
	t_env	*prev;
	t_env	*current;

	if (*head == NULL)
		return ;
	prev = NULL;
	current = *head;
	while (current != NULL)
	{
		if (ft_strcmp(current->str, target) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->str);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
