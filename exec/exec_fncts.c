/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fncts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:21:28 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 00:24:47 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_if_file_using_stat(char *file)
{
	struct stat	stats;

	if (stat(file, &stats) == 0)
		return (1);
	return (0);
}

void	ft_freepathandpaths(char *path, char **paths)
{
	free(path);
	ft_freearr(paths);
}

char	*ft_rtexpath(t_env *env, char *cmnd, int i, char *path)
{
	char	*command;
	char	**paths;
	char	*tmp;

	if (access(cmnd, F_OK) == 0)
		return (ft_strdup(cmnd));
	path = ft_fetchvalue("PATH", env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmnd);
		free(tmp);
		if (access(command, F_OK) == 0)
		{
			ft_freepathandpaths(path, paths);
			return (command);
		}
		free(command);
		i++;
	}
	ft_freepathandpaths(path, paths);
	return (NULL);
}

char	*ft_rtexpathve(t_env *env, char *cmnd, int i, char *path)
{
	char	*command;
	char	**paths;
	char	*tmp;

	if (access(cmnd, F_OK) == 0)
		return (ft_strdup(cmnd));
	path = ft_fetchvalue("PATH", env);
	if (!path)
		return (cmnd);
	paths = ft_split(path, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmnd);
		free(tmp);
		if (access(command, F_OK) == 0)
		{
			ft_freepathandpaths(path, paths);
			return (command);
		}
		free(command);
		i++;
	}
	ft_freepathandpaths(path, paths);
	return (cmnd);
}

char	**ft_env_to_array(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = ft_strdup(env->str);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
