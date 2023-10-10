/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:35:26 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/10 01:03:13 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_commands	*ft_createcommand(char **str)
{
	t_commands	*newnode;

	newnode = malloc(sizeof(t_commands));
	newnode->in_file = -1;
	newnode->cmd = str;
	newnode->next = NULL;
	newnode->out_file = 1;
	return (newnode);
}

void	ft_freecmd(t_commands *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		free(cmd->cmd[i]);
		i++;
	}
	free(cmd->cmd);
	free(cmd);
}

void	ft_freearr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_env(t_data **data, int fd)
{
	t_env	*cur;
	t_env	*node;

	node = (*data)->env;
	cur = (*data)->env;
	while (node)
	{
		if (ft_rulefinder(node->str, ft_strdup("_")))
			break ;
		if (!node->next)
			add_last_node(&(*data)->env, ft_strdup("_=env"));
		node = node->next;
	}
	while (cur)
	{
		ft_putstr_fd(cur->str, fd);
		ft_putchar_fd('\n', fd);
		cur = cur->next;
	}
	g_exit_status = 0;
}
