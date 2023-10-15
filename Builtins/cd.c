/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:32:08 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:12:43 by agoujdam         ###   ########.fr       */
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

void	ft_free_and_replace(t_data **data, char *str, int casse)
{
	if (casse == 1)
	{
		if ((*data)->path)
			free((*data)->path);
		(*data)->path = ft_strdup(str);
		ft_unsetandexport(data, NULL, ft_strdup(str), NULL);
	}
	else if (casse == 2)
	{
		if ((*data)->path)
			free((*data)->path);
		(*data)->path = (str);
		ft_unsetandexport(data, NULL, NULL, NULL);
	}
}

void	ft_set_exit_status_cd(int status)
{
	if (status == -1337)
		g_exit_status = 1;
}

void	ft_handle_lblanat(t_data **data, char *pwd, char *path, int status)
{
	char	*str;
	char	*lola;
	char	*pwdd;

	pwdd = ft_returncwd();
	str = ft_strjoin(pwd, "/");
	lola = ft_strjoin(str, path);
	if ((!ft_does_directory_exist(data, ft_strdup(lola))) && (!ft_strcmp(path,
				"..") || !ft_strcmp(path, ".")) && path && !status)
	{
		if (pwd)
		{
			ft_print_the_long_goddamn_sentence();
			ft_free_and_replace(data, lola, 1);
			if (pwd)
				status = ft_free_return(pwd, -1337);
		}
	}
	else
		ft_free_and_replace(data, pwd, 2);
	if (str)
		free(str);
	ft_free_cd_stuff(lola, pwdd, NULL);
	ft_set_exit_status_cd(status);
}

void	ft_cd(t_data **data, t_commands *comond, char *path)
{
	int	i;

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
