/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:32:08 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/12 10:24:32 by agoujdam         ###   ########.fr       */
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
		exit(1);
	}
	buffer = malloc(sizeof(char) * i);
	if (!buffer)
	{
		perror("Malloc");
		g_exit_status = 1;
		exit(1);
	}
	getcwd(buffer, i);
	if (!buffer)
		return (NULL);
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

	if (!path)
		return (0);
	if (stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
		return (ft_free_return(path, 1));
	return (ft_free_return(path, 0));
}

void	ft_free_cd_stuff(char *str, char *str2, char **str3)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	if (str3)
		ft_freearr(str3);
}

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

void	ft_print_the_long_goddamn_sentence(t_data **data)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}

void	ft_free_and_replace(t_data **data, char *str, int casse)
{
	if ((*data)->path)
		free((*data)->path);
	(*data)->path = str;
	if (casse == 1)
		ft_unsetandexport(data, NULL, ft_strdup(str), NULL);
	else if (casse == 2)
		ft_unsetandexport(data, NULL, NULL, NULL);
}

void	ft_handle_lblanat(t_data **data, char *pwd, char *path, int status)
{
	char	*str;
	char	*lola;
	char	*pwdd;

	pwdd = ft_returncwd();
	if ((!pwdd || !pwdd[0]) && path && !status)
	{
		str = ft_strjoin(pwd, "/");
		lola = ft_strjoin(str, path);
		if (pwd && !ft_does_directory_exist(data, ft_strdup(lola)))
		{
			ft_free_and_replace(data, lola, 1);
		}
		ft_free_cd_stuff(str, NULL, NULL);
	}
	else
		ft_free_and_replace(data, pwd, 2);
	ft_free_cd_stuff(NULL, pwdd, NULL);
	g_exit_status = 0;
}

void	ft_cd(t_data **data, t_commands *comond, char *path)
{
	char	*pwd;
	int		i;

	if (ft_handle_cd_errors(data, comond, path, NULL))
		return ;
	else
	{
		i = chdir(path);
		if (i != 0)
		{
			perror("Boubou_shell: cd");
			g_exit_status = 1;
			return ;
		}
	}
	ft_handle_lblanat(data, ft_returnpwd(data), path, i);
}
