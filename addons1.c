/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 01:04:25 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:13:50 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exportminimum(t_data **data)
{
	char	*pwd;
	char	*str;

	pwd = ft_returnpwd(data);
	str = ft_strjoin("PWD=", pwd);
	(*data)->env = ft_create_env_node(str);
	free(str);
	free(pwd);
	pwd = ft_itoa(1);
	str = ft_strjoin("shlvl=", pwd);
	ft_append_env_node(&(*data)->env, str);
	free(str);
	free(pwd);
	add_last_node(&(*data)->env, "_=env");
}

void	ft_exportminimumeq(t_data **data)
{
	char	*pwd;
	char	*str;

	(*data)->envnoeq = ft_create_env_node("OLDPWD");
	pwd = ft_returnpwd(data);
	str = ft_strjoin("PWD=", pwd);
	ft_append_env_node(&(*data)->envnoeq, str);
	free(pwd);
	free(str);
	pwd = ft_itoa(1);
	str = ft_strjoin("shlvl=", pwd);
	ft_append_env_node(&(*data)->envnoeq, str);
	free(str);
	free(pwd);
}

void	ft_printennv(t_env *head, int fd)
{
	t_env	*x;

	x = head;
	while (x)
	{
		ft_putstr_fd(x->str, fd);
		ft_putchar_fd('\n', fd);
		x = x->next;
	}
}

void	ft_initalizebasevalue(t_data **data)
{
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
	{
		perror("malloc");
		exit(1);
	}
	ft_exportminimum(data);
	ft_exportminimumeq(data);
}

void	ft_initializevalues(t_data **data, char **env)
{
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
	{
		perror("malloc");
		exit(1);
	}
	(*data)->env = ft_array_to_elist(env);
	(*data)->envnoeq = ft_array_to_elist(env);
	delete_last_node(&((*data)->env));
	delete_last_node(&((*data)->envnoeq));
	add_last_node(&((*data)->env), "_=env");
}
