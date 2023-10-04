/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 01:54:24 by afaqir            #+#    #+#             */
/*   Updated: 2023/03/15 23:56:28 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *ptr, char *buffer)
{
	char	*str;
	int		i;
	int		j;

	if (!ptr)
	{
		ptr = malloc(sizeof(char) * 1);
		if (!ptr)
			return (NULL);
		ptr[0] = 0;
	}
	if (!buffer)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(ptr) + ft_strlen(buffer) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (ptr[++i])
		str[i] = ptr[i];
	j = 0;
	while (buffer[j])
		str[i++] = buffer[j++];
	str[i] = '\0';
	free(ptr);
	return (str);
}

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
