/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:40:51 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 00:06:22 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unsetiden(t_env **env, t_env **envnocmd, char *iden)
{
	t_commands	*cmnd;
	t_data		*data;

	data = malloc(sizeof(t_data));
	data->env = (*env);
	data->envnoeq = (*envnocmd);
	cmnd = malloc(sizeof(t_commands));
	cmnd->cmd = malloc(sizeof(char *) * 3);
	cmnd->cmd[0] = ft_strdup("unset");
	cmnd->cmd[1] = ft_strdup(iden);
	cmnd->cmd[2] = NULL;
	ft_unset(&data, cmnd);
	free(cmnd->cmd[0]);
	free(cmnd->cmd[1]);
	free(cmnd->cmd);
	free(cmnd);
	free(data);
}

char	**ft_parse_args_norm(char *str, int condition, int i, char **returnval)
{
	if (i != 0)
	{
		if (str[i - 1] == '+')
		{
			returnval[0] = ft_substr(str, 0, i - 1);
			condition = 1;
		}
		else
			returnval[0] = ft_substr(str, 0, i);
	}
	else
		returnval[0] = ft_substr(str, 0, i);
	if (str[i + 1] == '\0')
		returnval[1] = ft_strdup("");
	else
		returnval[1] = ft_substr(str, i + 1, ft_strlen(str));
	if (condition == 1)
		returnval[2] = ft_strdup("+=");
	else
		returnval[2] = ft_strdup("=");
	returnval[3] = 0;
	return (returnval);
}

void	ft_free_strtmp(char *str, char *tmp)
{
	if (str)
		free(str);
	if (tmp)
		free(tmp);
}

char	*ft_exporttherulenorm(t_data **data, char *iden, char *value, char *str)
{
	char	*tmp;

	str = ft_strjoin(iden, "=");
	tmp = ft_strjoin(str, value);
	add_before_last_node(&(*data)->env, tmp);
	free(str);
	return (tmp);
}

void	ft_exporttherule(t_data **data, char *iden, char *value, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (ft_ruleexist(data, iden) && !value)
		return ;
	else if (ft_ruleexist(data, iden) && value)
	{
		str = ft_strjoin(iden, "=");
		tmp = ft_strjoin(str, value);
		ft_unsetiden(&(*data)->env, &(*data)->envnoeq, iden);
		add_before_last_node(&(*data)->env, tmp);
		add_before_last_node(&(*data)->envnoeq, tmp);
	}
	else
	{
		if (value)
			tmp = ft_exporttherulenorm(data, iden, value, str);
		else
			tmp = ft_strdup(iden);
		add_last_node(&(*data)->envnoeq, tmp);
	}
	ft_free_strtmp(str, tmp);
}
