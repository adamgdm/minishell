/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:03:38 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:11:09 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (array[0])
		free(array[0]);
	if (array[1])
		free(array[1]);
	if (array[2])
		free(array[2]);
	free(array);
}

void	ft_printenv(t_env *env, int fd)
{
	t_env	*x;
	char	**args;

	x = env;
	while (x)
	{
		args = ft_parse_args(x->str, 0, 0, NULL);
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(args[0], fd);
		if (args[1])
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(args[1], fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putchar_fd('\n', fd);
		ft_free_array(args);
		x = x->next;
	}
}

void	printargs(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("args[%d] = %s\n", i, args[i]);
		i++;
	}
}

int	ft_printerror(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

void	ft_export(t_data **data, char **args, int i, int fd)
{
	char	**arguments;

	if (!args[i])
	{
		ft_printenv(((*data)->envnoeq), fd);
		g_exit_status = 0;
		return ;
	}
	while (args[i])
	{
		arguments = ft_parse_args(args[i], 0, 0, NULL);
		if (!ft_checkerrors(args[i], arguments[0]))
		{
			if (ft_checkexportorappend(arguments[2]) == 1)
				ft_append(data, arguments[0], arguments[1]);
			else if (ft_checkexportorappend(arguments[2]) == 2)
				ft_exporttherule(data, arguments[0], arguments[1], NULL);
			g_exit_status = 0;
		}
		else
			g_exit_status = 1;
		i++;
		ft_freearr(arguments);
	}
}
