/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 01:01:49 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:50:15 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize(t_data **data, char **env, char *str)
{
	int	shlvl;

	if (!env || !(*env))
		ft_initalizebasevalue(data);
	else
		ft_initializevalues(data, env);
	(*data)->path = ft_returnpwd(data);
	str = ft_fetchvalue("SHLVL", (*data)->envnoeq);
	if (!str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(str);
		shlvl++;
	}
	free(str);
	if (shlvl == 1000)
		str = ft_strdup("");
	else
		str = ft_itoa(shlvl);
	ft_unsetiden(&((*data)->env), &((*data)->envnoeq), "SHLVL");
	ft_exporttherule(data, "SHLVL", str, NULL);
	free(str);
}

int	ft_doesmatch(char *str, char *qst)
{
	int	index;

	index = 0;
	if (!str || !qst)
		return (0);
	while (str[index] != '\0' || qst[index] != '\0')
	{
		if (str[index] != qst[index])
			return (0);
		index++;
	}
	if (!qst[index] && !str[index])
		return (1);
	return (0);
}

void	ft_sigints(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = (127 + sig) % 256;
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("\e[01;32mBoubou_shell> \e[0;37m", 1);
		exit(g_exit_status);
	}
}

void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = (127 + sig) % 256;
	}
}

int	ft_handle_more_than_one_arg(t_data **data, char *str)
{
	ft_check_if_directory(data, str, return_wsback(str));
	return (g_exit_status);
}
