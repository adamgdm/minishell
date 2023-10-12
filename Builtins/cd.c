/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:32:08 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/11 06:37:06 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_removethelastfolder(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] != '/')
		i--;
	i++;
	str[i] = '\0';
	return (str);
}

int	ft_free_return(char *str, int ret)
{
	free(str);
	return (ret);
}

int	ft_does_directory_exist(t_data **data)
{
	struct stat	stats;
	char		*path;

	path = ft_returnpwd(data);
	if (!path)
		return (0);
	path = ft_removethelastfolder(path);
	if (stat(path, &stats) == 0)
	{
		if (S_ISDIR(stats.st_mode))
			return (ft_free_return(path, 1));
		else
			return (ft_free_return(path, 0));
	}
	return(ft_free_return(path, 0));
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

char *ft_returnpathwithdots(t_data **data, char *pwd, int casee)
{
	char *path;

	if (pwd)
		free(pwd);
	pwd = fetchValue("PWD", (*data)->env);
	if (!pwd)
		return (NULL);
	if (casee == 1)
	{	
		path = ft_strjoin(pwd, "/..");
		free(pwd);
	}
	if (casee == 2)
		path = fetchValue("HOME", (*data)->env);
	return (path);
}

void	ft_unsetandexport(t_data **data, char *rts, char *pwd, char *str)
{
	char		**cmd;
	t_commands	*comond;

	if (!pwd)
		pwd = ft_returnpwd(data);
	if (ft_ruleexist(data, "OLDPWD"))
	{
		rts = fetchValue("PWD", (*data)->env);
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

void	ft_print_the_long_goddamn_sentence(t_data **data)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}

char *ft_eliminate(char *str)
{
	int	lenght;
	
	if (!str)
		return (NULL);
	lenght = ft_strlen(str) - 1;
		
}

void ft_handle_lblanat(t_data **data, char *pwd, char *path)
{
	char *str;
	char *lola;
	
	if (path && (!ft_strcmp(path, "..") || !(ft_strcmp(path, "."))) 
		&& !ft_does_directory_exist(data))
	{
		if (pwd)
		{
			str = ft_strjoin(pwd, "/");
			lola = ft_strjoin(str, path);
			free(str);
			str = ft_eliminate(lola);
			chdir(str);
			free(str);
		}
		ft_unsetandexport(data, NULL, lola, NULL);
	}
	else
	{
		ft_unsetandexport(data, NULL, NULL, NULL);
	}
	free(pwd);
	g_exit_status = 0;
}

void	ft_cd(t_data **data, t_commands *comond, char *path)
{
	char	*pwd;
	
	if (ft_handle_cd_errors(data, comond, path, NULL))
		return ;
	else
	{
		if ((!ft_strcmp(path, "..") || !(ft_strcmp(path, "."))) 
			&& !ft_does_directory_exist(data))
			ft_print_the_long_goddamn_sentence(data);
		else if (chdir(path) != 0)
		{
			perror("Boubou_shell: cd");
			g_exit_status = 1;
			return ;
		}
	}
	ft_handle_lblanat(data, fetchValue("PWD", (*data)->env), path);
}
