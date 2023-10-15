/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:06:42 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 00:06:43 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_ft_getvalue(char *str)
{
	int		i;
	char	*value;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (!str[i])
		return (NULL);
	value = ft_substr(str, i + 1, ft_strlen(str));
	return (value);
}

void	ft_append(t_data **data, char *iden, char *value)
{
	char	*rts;
	char	*str;
	char	*tmp;

	if (!ft_ruleexist(data, iden))
	{
		ft_exporttherule(data, iden, value, NULL);
	}
	else
	{
		rts = ft_returnrule((*data)->envnoeq, iden);
		str = ft_ft_getvalue(rts);
		if (str && value)
			tmp = ft_strjoin(str, value);
		else
			tmp = ft_strdup(value);
		ft_unsetiden(&((*data)->env), &((*data)->envnoeq), iden);
		ft_exporttherule(data, iden, tmp, NULL);
		free(tmp);
		free(rts);
		free(str);
	}
}
