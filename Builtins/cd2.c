/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:59:55 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:12:18 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_returncwd(void)
{
	int		i;
	char	*buffer;

	i = pathconf(".", _PC_PATH_MAX);
	if (!i || i == -1)
	{
		perror("Pathconf");
		g_exit_status = 1;
	}
	buffer = malloc(sizeof(char) * i);
	buffer[0] = '\0';
	if (!buffer)
	{
		perror("Malloc");
		g_exit_status = 1;
	}
	getcwd(buffer, i);
	if (!buffer)
	{
		perror("getcwd");
		g_exit_status = 1;
	}
	return (buffer);
}

int	ft_free_return(char *str, int ret)
{
	free(str);
	return (ret);
}

int	ft_does_directory_exist(t_data **data, char *path)
{
	struct stat	stats;

	(void)data;
	if (!path)
		return (0);
	if (stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
		return (ft_free_return(path, 1));
	return (ft_free_return(path, 0));
}
