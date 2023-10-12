/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:03:52 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/12 10:28:35 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_create_env_node(char *str)
{
	t_env	*newnode;

	newnode = (t_env *)malloc(sizeof(t_env));
	if (newnode)
	{
		newnode->str = ft_strdup(str);
		newnode->next = NULL;
	}
	return (newnode);
}

void	ft_append_env_node(t_env **head, char *str)
{
	t_env	*newnode;
	t_env	*current;

	newnode = ft_create_env_node(str);
	if (!newnode)
	{
		perror("malloc");
		exit(1);
	}
	if (*head == NULL)
	{
		*head = newnode;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}

t_env	*ft_array_to_elist(char **charArray)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = 0;
	while (charArray[i])
	{
		ft_append_env_node(&head, charArray[i]);
		i++;
	}
	return (head);
}

int	ft_rulefinder(char *cmd, char *arraytofind)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!arraytofind)
		return (0);
	if (!cmd)
	{
		free(arraytofind);
		return (0);
	}
	while (cmd[i])
	{
		if (i && !arraytofind[i])
			return (ft_free_return(arraytofind, 1));
		if (cmd[i] != arraytofind[i])
			return (ft_free_return(arraytofind, 0));
		i++;
	}
	if (arraytofind[i] == '\0')
		j = 1;
	free(arraytofind);
	return (j);
}

char	*ft_getvalue(char *input)
{
	char	*pwantour;
	int		sublength;
	char	*substring;

	pwantour = ft_strchr(input, '=');
	if (!pwantour)
	{
		return (NULL);
	}
	sublength = ft_strlen(pwantour + 1);
	substring = (char *)malloc(sublength + 1);
	if (!substring)
	{
		perror("malloc");
		exit(1);
	}
	ft_strcpy(substring, pwantour + 1);
	return (substring);
}

char	*ft_fetchvalue(char *str, t_env *head)
{
	t_env	*cur;
	char	*strr;
	int		i;

	cur = head;
	i = 0;
	while (cur)
	{
		if (ft_rulefinder(cur->str, ft_strjoin(str, "=")))
			break ;
		cur = cur->next;
		i++;
	}
	if (!cur)
		return (NULL);
	strr = ft_getvalue(cur->str);
	return (strr);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
