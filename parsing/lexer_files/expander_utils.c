/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:17 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/13 06:12:55 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	_custom_trim(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while ((*str)[i])
	{
		if ((*str)[i] && ((*str)[i] == ' ' || (*str)[i] == '\t'))
		{
			tmp = _append(tmp, ' ');
			while ((*str)[i] && ((*str)[i] == ' ' || (*str)[i] == '\t'))
				i++;
		}
		tmp = _append(tmp, (*str)[i]);
		i++;
	}
	free(*str);
	*str = tmp;
}

void	_join_the_word(char **save, char *tmp, t_data *data, t_token *head)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = ft_fetchvalue(tmp, data->env);
	if (tmp2)
	{
		tmp3 = *save;
		if (head->state == GENERAL)
			_custom_trim(&tmp2);
		*save = ft_strjoin(*save, tmp2);
		free(tmp);
		free(tmp2);
		free(tmp3);
	}
	else
		free(tmp);
}

void	_norminette(char **save, t_token *head, t_data *data, t_vars *vars)
{
	int		k;
	char	*tmp;

	(vars->i)++;
	k = vars->i;
	tmp = NULL;
	while (head->content[vars->i] && !ft_strchr("+*-?<>{}[]^()#%@\"'$&|;,/\t ",
			head->content[vars->i]) && !ft_isdigit(head->content[vars->i]))
		vars->i++;
	if (k == vars->i && head->content[vars->i] == '?')
		_join_exit_status(save, &vars->i);
	else if (k == vars->i && ft_isdigit(head->content[vars->i]))
		_join_digit(save, &head->content[k], data, &vars->i);
	else if (k == vars->i)
		_join_dollar_with_char(save, head->content, &vars->i);
	else
	{
		tmp = ft_substr(head->content, vars->j + 1, vars->i - vars->j - 1);
		_join_the_word(save, tmp, data, head);
	}
	vars->j = vars->i;
}
