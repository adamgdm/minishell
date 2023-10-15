/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fncts2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:26:04 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 05:08:46 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_exit_status(void)
{
	if (WIFSIGNALED(g_exit_status))
	{
		g_exit_status = g_exit_status + 128 % 256;
		if (g_exit_status == 131)
			ft_putstr_fd("\nQuit: 3\n", 1);
		else if (g_exit_status == 130)
			ft_putstr_fd("\n", 1);
	}
	else if (WEXITSTATUS(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
}

void	ft_set_up_io_mid_redirection(t_commands *cmnd)
{
	if (cmnd->out_file == 1 && cmnd->in_file == 0)
	{
		dup2(cmnd->pipefd[1], 1);
		dup2(cmnd->pipefd[0], 0);
	}
	else
	{
		if (cmnd->out_file == 1 && cmnd->in_file != 0)
		{
			dup2(cmnd->in_file, 0);
			dup2(cmnd->pipefd[1], 1);
		}
		else if (cmnd->out_file != 1 && cmnd->in_file == 0)
		{
			dup2(cmnd->out_file, 1);
			dup2(cmnd->pipefd[0], 0);
		}
		else
		{
			dup2(cmnd->in_file, 0);
			dup2(cmnd->out_file, 1);
		}
	}
}

void	ft_execute_child_mid_process(t_data **data, t_commands *cmnd)
{
	signal(SIGINT, ft_sigints);
	signal(SIGQUIT, ft_sigints);
	ft_set_up_io_mid_redirection(cmnd);
	ft_ft_clozi_pipes(cmnd);
	if (ft_builtinechoexpwithpara(data, cmnd) == 0)
		ft_execvee(cmnd->cmd, data);
	else
		exit(0);
}

void	ft_execute_middle_commandz(t_data **data, t_commands *cmnd)
{
	if (ft_check_cmd(data, cmnd, NULL))
	{
		if (ft_builtincdexpwithtpara(data, cmnd))
			return ;
		cmnd->pid = fork();
		if (cmnd->pid == 0)
			ft_execute_child_mid_process(data, cmnd);
		else
		{
			ft_execute_parent_process(&cmnd);
		}
	}
}

t_commands	*return_node_after_error(t_commands *cmnd)
{
	t_commands	*current;

	current = cmnd;
	while (!current->next)
		current = current->next;
	while (current)
	{
		if (current->error_exist)
			return (current);
		current = current->previous;
	}
	return (cmnd);
}
