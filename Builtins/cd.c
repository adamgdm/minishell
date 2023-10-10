/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:32:08 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/10 01:07:18 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_cd_stuff(char *str, char *str2, char **str3)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	if (str3)
		ft_freearr(str3);
}

void	ft_unsetandexport(t_data **data, char *rts, char *pwd, char *str)
{
	char		**cmd;
	t_commands	*comond;

	pwd = ft_returnpwd();
	if (ft_ruleexist(data, "OLDPWD"))
	{
		comond = ft_createcommand(ft_split("unset OLDPWD", ' '));
		ft_unset(data, comond);
		ft_freecmd(comond);
		str = ft_strjoin("export OLDPWD=", rts);
		cmd = ft_split(str, ' ');
		ft_export(data, cmd, 1, 1);
		ft_free_cd_stuff(str, NULL, cmd);
	}
	if (ft_ruleexist(data, "PWD"))
	{
		comond = ft_createcommand(ft_split("unset PWD", ' '));
		ft_unset(data, comond);
		ft_freecmd(comond);
		str = ft_strjoin("export PWD=", pwd);
		cmd = ft_split(str, ' ');
		ft_export(data, cmd, 1, 1);
		ft_free_cd_stuff(str, NULL, cmd);
	}
	free(pwd);
}

char	*ft_return_home_or_pwd(t_data **data, char *path, char *lol)
{
	if (!path || (path && (ft_strchr(path, '~'))))
	{
		lol = fetchValue("HOME", (*data)->env);
		if (!lol)
		{
			ft_putstr_fd("Boubou_shell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (lol);
	}
	else if (path && ft_strchr(path, '-'))
	{
		lol = fetchValue("OLDPWD", (*data)->env);
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

void	ft_cd(t_data **data, t_commands *comond, char *path)
{
	char	*pwd;

	pwd = fetchValue("PWD", (*data)->env);
	if (ft_handle_cd_errors(data, comond, path, NULL))
	{
		free(pwd);
		return ;
	}
	else
	{
		if (chdir(path) != 0)
		{
			perror("Boubou_shell: cd");
			free(pwd);
			g_exit_status = 1;
			return ;
		}
	}
	ft_unsetandexport(data, pwd, NULL, NULL);
	free(pwd);
	g_exit_status = 0;
}
