/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:06:00 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/13 22:03:33 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_parser_norm4(t_token *current, int *in_file, t_data *data)
{
	int	*fd;

	if (current->next->state == GENERAL)
		fd = _here_doc(current->next->content, 1, data);
	else
		fd = _here_doc(current->next->content, 0, data);
	*in_file = fd[0];
	free(fd);
}

void	_close_all_pipes(t_commands *head)
{
	t_commands	*current;

	current = head;
	while (current)
	{
		if (current->pipefd[0] != -1)
			close(current->pipefd[0]);
		if (current->pipefd[1] != -1)
			close(current->pipefd[1]);
		current = current->next;
	}
}

int	_parser_norm5(t_commands **head, int **result_pipe, t_vars3 *vars,
		int *previous_pipe)
{
	int			p[2];
	t_commands	*new;

	(*result_pipe)[0] = *previous_pipe;
	if (pipe(p) == -1)
	{
		_close_all_pipes(*head);
		perror("pipe");
		g_exit_status = 1;
		return (1);
	}
	(*result_pipe)[1] = p[1];
	*previous_pipe = p[0];
	new = _create_command(vars);
	_add_command(head, new);
	vars->commands = NULL;
	*result_pipe = malloc(sizeof(int) * 2);
	(*result_pipe)[0] = -1;
	(*result_pipe)[1] = -1;
	vars->already_printed = 0;
	vars->error = 0;
	vars->in_file = 0;
	vars->out_file = 1;
	return (0);
}

void	_initialize_vars(t_vars3 *vars)
{
	vars->commands = NULL;
	vars->in_file = 0;
	vars->out_file = 1;
	vars->error = 0;
	vars->already_printed = 0;
	vars->previous_pipe = -1;
	vars->result_pipe = malloc(sizeof(int) * 2);
	vars->result_pipe[0] = -1;
	vars->result_pipe[1] = -1;
}

int	_parser_norm6(t_commands **head, t_token *current, t_vars3 *vars,
		t_data *data)
{
	if (current->type == WORD)
		vars->commands = _append_string(vars->commands, current->content);
	if (current->type == REDIRECT_OUT)
		_do_norm(current, vars);
	if (current->type == REDIRECT_APPEND)
	{
		_parser_norm2(current, &vars->out_file, &vars->error,
			&vars->already_printed);
		_parser_free_norm(current);
	}
	if (current->type == REDIRECT_IN || current->type == HERE_DOC)
		_do_norm3(current, vars, data);
	if (current->type == PIPE)
	{
		if (_parser_norm5(head, &vars->result_pipe, vars, &vars->previous_pipe))
		{
			free(current->content);
			current->content = NULL;
			_print_commands(*head);
			free_commands2(*head);
			return (1);
		}
		free(current->content);
		current->content = NULL;
	}
	return (0);
}
