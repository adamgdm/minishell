/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fncts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:21:28 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/10 20:21:29 by agoujdam         ###   ########.fr       */
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
	path = fetchValue("PATH", env);
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
	path = fetchValue("PATH", env);
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

t_execcommand	*ft_returndataforexec(t_data **data, t_commands *cmnd)
{
	t_execcommand	*execcommand;

	execcommand = malloc(sizeof(t_execcommand));
	execcommand->command = ft_rtexpath((*data)->env, cmnd->cmd[0], 0, NULL);
	execcommand->args = ft_changeelement(cmnd->cmd, 0, execcommand->command);
	execcommand->environement = ft_env_to_array((*data)->env);
	return (execcommand);
}

t_execcommand	*ft_returndataforexecve(t_data **data, t_commands *cmnd)
{
	t_execcommand	*execcommand;

	execcommand = malloc(sizeof(t_execcommand));
	execcommand->command = ft_rtexpathve((*data)->env, cmnd->cmd[0], 0, NULL);
	execcommand->args = ft_changeelement(cmnd->cmd, 0, execcommand->command);
	execcommand->environement = ft_env_to_array((*data)->env);
	return (execcommand);
}

void	ft_execvee(char **cmd, t_data **data)
{
	t_execcommand	*excmd;
	t_commands		*cmnd;

	cmnd = ft_createcommand(cmd);
	excmd = ft_returndataforexecve(data, cmnd);
	g_exit_status = execve(excmd->command, excmd->args, excmd->environement);
	ft_putstr_fd("Boubou_shell: ", 2);
	ft_putstr_fd(excmd->command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(g_exit_status = 1);
}

char	**ft_changeelement(char **arr, int index, char *newelement)
{
	char	**returnval;
	int		i;

	i = 0;
	if (!newelement)
		return (arr);
	returnval = malloc(sizeof(char *) * (ft_count(arr) + 1));
	while (arr[i])
	{
		if (i == index)
			returnval[i] = ft_strdup(newelement);
		else
			returnval[i] = ft_strdup(arr[i]);
		i++;
	}
	returnval[i] = NULL;
	return (returnval);
}

void	ft_freeexeccommand(t_execcommand *execcommand)
{
	if (execcommand->command)
	{
		free(execcommand->command);
		ft_freearr(execcommand->args);
	}
	ft_freearr(execcommand->environement);
	free(execcommand);
}
