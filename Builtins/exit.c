/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:37:46 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/09 19:38:07 by agoujdam         ###   ########.fr       */
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
		temp = current;
		current = current->next;
		if (temp->cmd != NULL)
		{
			while (temp->cmd[i] != NULL)
			{
				free(temp->cmd[i]);
				i++;
			}
			free(temp->cmd);
		}
		free(temp->pipefd);
		free(temp);
	}
}

void	ft_exit(t_data **data, t_commands *cmnds)
{
	printf("exit\n");
	if (cmnds)
		free_commands(cmnds);
	free_t_data(data);
	exit(g_exit_status);
}
