/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 06:07:43 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/13 06:12:10 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*_expand_word2(char *content, t_data *data)
{
	t_vars	vars;

	vars.i = 0;
	vars.j = 0;
	vars.k = 0;
	vars.save = ft_strdup("");
	while (content[vars.i])
	{
		if (content[vars.i] == '$')
			_norminette_doc(&vars.save, content, data, &vars);
		else if (content[vars.i] && content[vars.i] != '$')
		{
			vars.save = _append(vars.save, content[vars.i]);
			vars.i++;
			vars.j = vars.i;
		}
	}
	free(content);
	return (vars.save);
}

void	_norminette_doc(char **save, char *content, t_data *data, t_vars *vars)
{
	int		k;
	char	*tmp;

	(vars->i)++;
	k = vars->i;
	tmp = NULL;
	while (content[vars->i] && !ft_strchr("+*-?=<>{}[]^()#%@\"'$&|;,/\t ",
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
		_join_the_word_doc(save, tmp, data);
	}
	vars->j = vars->i;
}

void	_join_the_word_doc(char **save, char *tmp, t_data *data)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = ft_fetchvalue(tmp, data->env);
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
