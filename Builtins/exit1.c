/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:01:27 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:11:38 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->str);
		free(temp);
	}
}

void	free_t_data(t_data **dat)
{
	t_data	*data;

	data = *dat;
	if (data != NULL)
	{
		free_env_list(data->env);
		free_env_list(data->envnoeq);
		if (data->path)
			free(data->path);
		free(data);
	}
}

void	free_commands(t_commands *head)
{
	t_commands	*current;
	t_commands	*temp;
	int			i;

	i = 0;
	current = head;
	while (current != NULL)
	{
		i = 0;
		temp = current;
		current = current->next;
		if (temp->cmd != NULL)
		{
			while (temp->cmd[i] != NULL)
			{
				free(temp->cmd[i]);
				i++;
			}
			free(temp->cmd[i]);
			free(temp->cmd);
		}
		free(temp->pipefd);
		free(temp);
	}
}

int	ft_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
