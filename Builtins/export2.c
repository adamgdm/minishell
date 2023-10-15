/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:04:37 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:10:48 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_parse_args(char *str, int condition, int i, char **returnval)
{
	returnval = malloc(sizeof(char *) * 4);
	while (str[i])
	{
		condition = 0;
		if (str[i] == '=')
			return (ft_parse_args_norm(str, condition, i, returnval));
		i++;
	}
	returnval[0] = ft_strdup(str);
	returnval[1] = 0;
	returnval[2] = 0;
	returnval[3] = 0;
	return (returnval);
}

int	ft_freeretone(char *str)
{
	free(str);
	return (1);
}

char	*ft_returnrule(t_env *env, char *rts)
{
	t_env	*x;
	char	*str;

	x = env;
	while (x)
	{
		str = ft_strjoin(rts, "=");
		if (ft_rulefinder(x->str, str))
			return (ft_strdup(x->str));
		x = x->next;
	}
	return (0);
}

int	ft_ruleexist(t_data **data, char *iden)
{
	t_env	*x;
	char	*str;
	char	*rule;

	if (!data || !(*data) || !iden)
		return (0);
	x = (*data)->env;
	str = ft_strjoin(iden, "=");
	while (x)
	{
		rule = ft_strdup(str);
		if (ft_rulefinder(x->str, rule))
			return (ft_freeretone(str));
		x = x->next;
	}
	x = (*data)->envnoeq;
	while (x)
	{
		if (!ft_strcmp(x->str, iden))
			return (ft_freeretone(str));
		x = x->next;
	}
	free(str);
	return (0);
}

int	ft_checkexportorappend(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (2);
	if (str[0] == '+')
		return (1);
	if (str[0] == '=')
		return (2);
	return (0);
}
