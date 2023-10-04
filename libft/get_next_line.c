/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 01:48:48 by afaqir            #+#    #+#             */
/*   Updated: 2023/03/16 02:42:12 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin(char *ptr, char *buffer)
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

char	*ft_read_full_line(int fd, char *ptr)
{
	int		k;
	char	*buffer;

	k = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (k && !ft_strchr(ptr, '\n'))
	{
		k = read(fd, buffer, BUFFER_SIZE);
		if (k == -1)
		{
			free (ptr);
			free (buffer);
			return (NULL);
		}
		buffer[k] = '\0';
		ptr = ft_strjoin(ptr, buffer);
	}
	free(buffer);
	return (ptr);
}

char	*ft_updated_line(char *ptr)
{
	char	*str;
	int		i;

	i = 0;
	if (!ptr[i])
		return (NULL);
	while (ptr[i] && ptr[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (ptr[i] && ptr[i] != '\n')
	{
		str[i] = ptr[i];
		i++;
	}
	if (ptr[i] == '\n')
	{
		str[i] = ptr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_adjust_line(char *ptr)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (ptr[i] && ptr[i] != '\n')
		i++;
	if (ptr[i] == '\n')
	{
		str = malloc(sizeof(char) * (ft_strlen(ptr) - i + 1));
		if (!str)
			return (NULL);
		i++;
		j = 0;
		while (ptr[i])
			str[j++] = ptr[i++];
		str[j] = '\0';
		free(ptr);
		return (str);
	}
	else
	{
		free(ptr);
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ptr = ft_read_full_line(fd, ptr);
	if (!ptr)
		return (NULL);
	line = ft_updated_line(ptr);
	ptr = ft_adjust_line(ptr);
	return (line);
}
