/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:18:52 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/12 09:22:58 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_which_line(char **envp, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (envp[i])
	{
		while (envp[i][j])
		{
			if (envp[i][j] == str[k])
			{
				k++;
				if (k == ft_strlen(str) && j == k - 1)
					return (i);
			}
			else
				k = 0;
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

char	*ft_line_w_out_path(char *str, int len)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	line = (char *)malloc(sizeof(char) * len);
	if (!line)
		return (NULL);
	while (str[i] != ':')
		i++;
	while (j <= len)
	{
		line[j] = str[i];
		j++;
		i++;
	}
	return (line);
}

char	**ft_find_path(char **envp, t_env *head)
{
	char	*line;
	char	**str;

	line = ft_fetchvalue("PATH", head);
	str = ft_split(line, ':');
	return (str);
}

char	*ft_makethelist(char *cmd, char **path, t_env *head)
{
	char	*command;
	char	*hehe;
	int		i;

	i = 0;
	while (path[i])
	{
		hehe = ft_strjoin(path[i], "/");
		command = ft_strjoin(hehe, cmd);
		free(hehe);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	ft_free_pipes(int **pipes, t_commands *cmnd, int i)
{
	while (i >= 0)
	{
		if (pipes[i])
			free(pipes[i]);
		i--;
	}
	free(pipes);
}

int	**ft_create_pipes(t_commands *cmnd)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * (ft_count_how_many_pipes(cmnd) + 1));
	if (!pipes)
		return (NULL);
	while (cmnd)
	{
		if (cmnd->next)
		{
			pipes[i] = malloc(sizeof(int) * 2);
			if (!pipes[i])
				return (ft_free_pipes(pipes, cmnd, i), NULL);
			if (pipe(pipes[i]) == -1)
				return (ft_free_pipes(pipes, cmnd, i), NULL);
		}
		else
			pipes[i] = NULL;
		i++;
		cmnd = cmnd->next;
	}
	return (pipes);
}

int	ft_count_how_many_pipes(t_commands *cmnd)
{
	int	i;

	i = 0;
	while (cmnd)
	{
		if (cmnd)
			i++;
		cmnd = cmnd->next;
	}
	return (i);
}

int	ft_check_last_character(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == c)
		return (1);
	return (0);
}
