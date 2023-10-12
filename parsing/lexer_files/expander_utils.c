/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:17 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 01:11:04 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_join_exit_status(char **save, int *i)
{
	char	*tmp3;
	char	*tmp;

	tmp3 = *save;
	tmp = ft_itoa(g_exit_status);
	*save = ft_strjoin(*save, tmp);
	free(tmp3);
	free(tmp);
	(*i)++;
}

void	_join_digit(char **save, char *content, t_data *data, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = fetchValue(content, data->env);
	if (tmp2)
	{
		tmp = *save;
		*save = ft_strjoin(*save, tmp2);
		free(tmp);
		free(tmp2);
	}
	(*i)++;
}

void	_join_dollar_with_char(char **save, char *content, int *i)
{
	if (!content[*i])
		*save = _append(*save, '$');
	else
	{
		*save = _append(*save, '$');
		*save = _append(*save, content[*i]);
		(*i)++;
	}
}

void	_join_the_word(char **save, char *tmp, t_data *data)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = fetchValue(tmp, data->env);
	if (tmp2)
	{
		tmp3 = *save;
		*save = ft_strjoin(*save, tmp2);
		free(tmp);
		free(tmp2);
		free(tmp3);
	}
	else
		free(tmp);
}

void	_norminette(char **save, char *content, t_data *data, t_vars *vars)
{
	int		k;
	char	*tmp;

	(vars->i)++;
	k = vars->i;
	tmp = NULL;
	while (content[vars->i] && !ft_strchr("+*-?<>{}[]^()#%@\"'$&|;,/\t ",
			content[vars->i]) && !ft_isdigit(content[vars->i]))
		vars->i++;
	if (k == vars->i && content[vars->i] == '?')
		_join_exit_status(save, &vars->i);
	else if (k == vars->i && ft_isdigit(content[vars->i]))
		_join_digit(save, &content[k], data, &vars->i);
	else if (k == vars->i)
		_join_dollar_with_char(save, content, &vars->i);
	else
	{
		tmp = ft_substr(content, vars->j + 1, vars->i - vars->j - 1);
		_join_the_word(save, tmp, data);
	}
	vars->j = vars->i;
}
