/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:37:46 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:11:50 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	printf("exit\n");
	if (cmnds)
	{
		ft_error_exit(cmnds);
		free_commands(cmnds);
	}
	free_t_data(data);
	exit(g_exit_status);
}
