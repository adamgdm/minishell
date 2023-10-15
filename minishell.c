/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:50:26 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/15 01:03:40 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 55;

void	_print_token(t_token *token)
{
	printf("-----------------------------------------------\n");
	while (token)
	{
		printf("[content]: %s\n", token->content);
		printf("[type]: %d\n", token->type);
		printf("[state]: %d\n", token->state);
		printf("[before_expanded]: %s\n", token->before_expanded);
		printf("[space_check]: %d\n", token->space_check);
		printf("-----------------------------------------------\n");
		token = token->next;
	}
}

void	_print_commands(t_commands *commands)
{
	int	i;

	i = 0;
	printf("$-----------------commands---------------------$\n");
	while (commands)
	{
		_print_array(commands->cmd);
		printf("in_file: %d\n", commands->in_file);
		printf("out_file: %d\n", commands->out_file);
		printf("error_exist: %d\n", commands->error_exist);
		printf("pipefd[0]: %d  ", commands->pipefd[0]);
		printf("pipefd[1]: %d\n", commands->pipefd[1]);
		printf("-----------------------------------------------\n");
		commands = commands->next;
		i++;
	}
}

void	free_commands2(t_commands *head)
{
	t_commands	*current;
	t_commands	*temp;
	int			i;

	i = 0;
	current = head;
	while (current != NULL)
	{
		i = 0;
		temp = current;
		current = current->next;
		while (temp->cmd && temp->cmd[i] != NULL)
		{
			printf("freeing %s\n", temp->cmd[i]);
			i++;
		}
		free(temp->cmd[i]);
		free(temp->cmd);
		printf("freeing %d %d\n", temp->pipefd[0], temp->pipefd[1]);
		free(temp->pipefd);
		free(temp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data		*g_data;

	(void)av;
	g_data = NULL;
	if (ac != 1)
		return (ft_handle_more_than_one_arg(&g_data, av[1]));
	ft_initialize(&g_data, envp, NULL);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (_launch_shell(g_data));
	return (g_exit_status);
}
