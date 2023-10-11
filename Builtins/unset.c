/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:01:38 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/10 20:03:10 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_freenode(t_env *node)
{
	free(node->str);
	free(node);
}

void	ft_deletenodebycontent(t_env **head, char *target)
{
	t_env	*current;
	t_env	*prev;

	if (*head == NULL)
		return ;
	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (strcmp(current->str, target) == 0)
		{
			if (prev == NULL)
			{
				*head = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			ft_freenode(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_rulefinderanddelete_eq(t_data **data, char *rule)
{
	t_env	*x;
	t_env	*y;
	char	*str;
	int		i;

	str = NULL;
	x = (*data)->env;
	i = 1;
	while (x)
	{
		if (ft_rulefinder(x->str, ft_strdup(rule)))
		{
			str = ft_strdup(x->str);
			ft_deletenodebycontent(&(*data)->env, x->str);
			ft_deletenodebycontent(&(*data)->envnoeq, str);
			break ;
		}
		y = x;
		x = x->next;
		i++;
	}
	if (str)
		free(str);
	free(rule);
}

void	ft_rulefinderanddelete(t_data **data, char *rule)
{
	t_env	*x;
	t_env	*y;
	int		i;

	x = (*data)->envnoeq;
	i = 1;
	while (x)
	{
		if (!ft_strcmp(x->str, rule))
		{
			ft_deletenodebycontent(&(*data)->envnoeq, x->str);
			break ;
		}
		y = x;
		x = x->next;
	}
	free(rule);
}

void	ft_unset(t_data **data, t_commands *cmnd)
{
	t_env	*x;
	t_env	*y;
	int		i;
	int		count;

	count = ft_count(cmnd->cmd);
	i = 1;
	while (i < count)
	{
		ft_rulefinderanddelete_eq(data, ft_strjoin(cmnd->cmd[i], "="));
		i++;
	}
	i = 1;
	while (i < count)
	{
		ft_rulefinderanddelete(data, ft_strdup(cmnd->cmd[i]));
		i++;
	}
	g_exit_status = 0;
}
