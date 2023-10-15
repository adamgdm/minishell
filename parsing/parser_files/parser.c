/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:06:11 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/15 01:51:03 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**_append_string(char **commands, char *content)
{
	int		i;
	char	**new;

	i = 0;
	while (commands && commands[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (commands && commands[i])
	{
		new[i] = commands[i];
		i++;
	}
	new[i] = content;
	new[i + 1] = NULL;
	if (commands)
		free(commands);
	return (new);
}

void	_print_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		if (array[i] == NULL)
		{
			return ;
		}
		printf("array[%d]: %s\n", i, array[i]);
		i++;
	}
}

int	_is_there_space_or_tab(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == ' ' || content[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

t_commands	*_parser(t_token **result, t_data *data)
{
	t_vars3		vars;
	t_token		*current;
	t_commands	*head;
	t_commands	*new;

	current = *result;
	head = NULL;
	_initialize_vars(&vars);
	while (current)
	{
		if (_parser_norm6(&head, current, &vars, data))
			return (NULL);
		current = current->next;
	}
	vars.result_pipe[0] = vars.previous_pipe;
	vars.result_pipe[1] = -1;
	new = _create_command(&vars);
	_add_command(&head, new);
	return (head);
}
