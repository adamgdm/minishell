/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fncts6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:30:10 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:18:58 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtincdexpwithtpara(t_data **data,
													t_commands *cmnd)
{
	if (ft_doesmatch(cmnd->cmd[0], "cd"))
	{
		ft_cd(data, cmnd, cmnd->cmd[1]);
		return (1);
	}
	else if (ft_doesmatch(cmnd->cmd[0], "exit"))
	{
		ft_exit(data, cmnd);
		return (1);
	}
	else if (ft_doesmatch(cmnd->cmd[0], "unset"))
	{
		ft_unset(data, cmnd);
		return (1);
	}
	else if ((ft_doesmatch(cmnd->cmd[0], "export") && cmnd->cmd[1]))
	{
		ft_export(data, cmnd->cmd, 1, cmnd->out_file);
		return (1);
	}
	return (0);
}

int	ft_check_whether_builtins(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

void	ft_print_er(char *str, char *err, int exit_status)
{
	ft_putstr_fd("Boubou_shell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (err)
		ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = exit_status;
}

char	*return_wsback(char *str)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			j = i;
		i++;
	}
	new = ft_substr(str, 0, j);
	return (new);
}

void	ft_handle_path_existance(t_data **data, char *cmd)
{
	if (ft_ruleexist(data, "PATH"))
		ft_print_er(cmd, "command not found", 127);
	else
		ft_print_er(cmd, "No such file or directory", 127);
}
