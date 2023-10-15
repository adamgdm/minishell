/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fncts5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:29:10 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:09:12 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_if_directory(t_data **data, char *cmd, char *str)
{
	struct stat	sb;

	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			ft_print_er(cmd, "Is a directory", 126);
		}
		else
		{
			if (ft_rulefinder(cmd, ft_strdup("./")) && access(cmd, F_OK) == 0)
				ft_print_er(cmd, "Permission denied", 126);
			else if ((access(cmd, F_OK) == 0 || access(cmd, X_OK) == 0)
				|| (access(str, F_OK) == 0 || access(str, X_OK) == 0))
				ft_print_er(cmd, "Not a directory", 126);
			else
				ft_print_er(cmd, "No such file or directory", 127);
		}
	}
	else
		ft_handle_path_existance(data, cmd);
	if (str)
		free(str);
}

int	ft_check_if_executable(char *str)
{
	if (ft_rulefinder(str, ft_strdup("./")) && access(str, F_OK) == 0
		&& access(str, X_OK) == 0)
	{
		return (1);
	}
	return (0);
}

int	ft_check_cmd(t_data **data, t_commands *comond, char *cmd)
{
	char	*str;

	if (!comond->cmd || !comond->cmd[0])
		return (0);
	cmd = comond->cmd[0];
	if (comond->error_exist)
	{
		g_exit_status = 1;
		return (0);
	}
	if (ft_check_whether_builtins(cmd))
		return (1);
	str = ft_rtexpath((*data)->env, cmd, 0, NULL);
	if (str)
	{
		free(str);
		return (1);
	}
	if (ft_check_if_executable(cmd))
		return (1);
	ft_check_if_directory(data, cmd, return_wsback(cmd));
	return (0);
}

void	ft_pwd_pre(char *str, t_data **data, int fd)
{
	if (!str)
		ft_pwd(data, fd);
	else
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		g_exit_status = 1;
	}
}

void	ft_env_pre(char *str, t_data **data, int fd)
{
	if (!str)
		ft_env(data, fd);
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd("Too many arguments\n", 2);
		g_exit_status = 127;
	}
}
