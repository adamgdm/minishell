/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:59:51 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:12:27 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unsetandex(t_data **data, char **cmd, char *str, char *rts)
{
	ft_export(data, cmd, 1, 1);
	ft_free_cd_stuff(str, rts, cmd);
}

void	ft_unsetandexport(t_data **data, char *rts, char *pwd, char *str)
{
	char		**cmd;
	t_commands	*comond;

	if (!pwd)
		pwd = ft_returnpwd(data);
	if (ft_ruleexist(data, "OLDPWD"))
	{
		rts = ft_fetchvalue("PWD", (*data)->env);
		comond = ft_createcommand(ft_split("unset OLDPWD", ' '));
		ft_unset(data, comond);
		ft_freecmd(comond);
		str = ft_strjoin("export OLDPWD=", rts);
		cmd = ft_split(str, ' ');
		ft_unsetandex(data, cmd, str, rts);
	}
	if (ft_ruleexist(data, "PWD"))
	{
		comond = ft_createcommand(ft_split("unset PWD", ' '));
		ft_unset(data, comond);
		ft_freecmd(comond);
		str = ft_strjoin("export PWD=", pwd);
		cmd = ft_split(str, ' ');
		ft_unsetandex(data, cmd, str, NULL);
	}
	free(pwd);
}

char	*ft_return_home_or_pwd(t_data **data, char *path, char *lol)
{
	if (!path || (path && (ft_strchr(path, '~'))))
	{
		lol = ft_fetchvalue("HOME", (*data)->env);
		if (!lol)
		{
			ft_putstr_fd("Boubou_shell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (lol);
	}
	else if (path && ft_strchr(path, '-'))
	{
		lol = ft_fetchvalue("OLDPWD", (*data)->env);
		if (!lol)
		{
			ft_putstr_fd("Boubou_shell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		return (lol);
	}
	return (NULL);
}

int	ft_handle_cd_errors(t_data **data, t_commands *cmnd, char *path, char *lol)
{
	if (cmnd->cmd[1] && cmnd->cmd[2])
	{
		ft_putstr_fd("Boubou_shell: cd: too many arguments\n", 2);
		return (g_exit_status = 1);
	}
	if (!path || (path && (ft_strchr(path, '~') || ft_strchr(path, '-'))))
	{
		lol = ft_return_home_or_pwd(data, path, lol);
		if (!lol)
			return (g_exit_status = 1);
		if (chdir(lol) != 0)
			return (ft_chdir_error_print(lol));
		else
		{
			free(lol);
			g_exit_status = 0;
			return (1);
		}
		free(lol);
	}
	return (0);
}

void	ft_print_the_long_goddamn_sentence(void)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	g_exit_status = 1;
}
