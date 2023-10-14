/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:37:46 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/14 08:55:02 by agoujdam         ###   ########.fr       */
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

int	ft_isbiggerthankbir(char *str)
{
	int		i;
	size_t	res;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res > 9223372036854775807)
		return (1);
	return (0);
}

long long	ft_atoll(char *str)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = (-1);
		i++;
	}
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	ft_isnumber(char *str)
{
	if (ft_number(str) == 0)
		return (0);
	if (ft_isbiggerthankbir(str) == 1)
		return (0);
	return (1);
}

void	ft_error_exit(t_commands *cmnds)
{
	if (cmnds->cmd[1] != NULL)
	{
		if (ft_isnumber(cmnds->cmd[1]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required\n",
					cmnds->cmd[1]);
			g_exit_status = 255;
		}
		else if (cmnds->cmd[2] != NULL)
		{
			printf("minishell: exit: too many arguments\n");
			g_exit_status = 1;
		}
		else
			g_exit_status = ft_atoll(cmnds->cmd[1]);
	}
}

void	ft_exit(t_data **data, t_commands *cmnds)
{
	//system("leaks minishell");
	printf("exit\n");
	if (cmnds)
	{
		ft_error_exit(cmnds);
		free_commands(cmnds);
	}
	free_t_data(data);
	exit(g_exit_status);
}
