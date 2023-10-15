/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:18:52 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 00:23:43 by agoujdam         ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 < *s2)
		return (-1);
	else if (*s1 > *s2)
		return (1);
	return (0);
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
