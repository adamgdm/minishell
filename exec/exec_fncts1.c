/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fncts1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:25:07 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 00:25:08 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_execvee(char **cmd, t_data **data)
{
	t_execcommand	*excmd;
	t_commands		*cmnd;

	cmnd = ft_createcommand(cmd);
	excmd = ft_returndataforexecve(data, cmnd);
	execve(excmd->command, excmd->args, excmd->environement);
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
