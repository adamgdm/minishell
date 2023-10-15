/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_fncts_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:32:03 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 02:04:44 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chdir_error_print(char *path)
{
	perror("Boubou_shell: cd");
	free(path);
	return (g_exit_status = 1);
}

int	ft_checkerrors(char *command, char *identifier)
{
	int	i;

	i = 0;
	if (identifier[0] != '_' && !ft_isalpha(identifier[0]))
		return (ft_printerror(identifier));
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (ft_printerror(command));
		i++;
	}
	return (0);
}

int	ft_check_last_character(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == c)
		return (1);
	return (0);
}
