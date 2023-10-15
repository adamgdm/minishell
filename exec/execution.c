/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:00:52 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 04:53:47 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_processes(t_commands *cmnd)
{
	t_commands	*current;

	current = cmnd;
	while (current)
	{
		waitpid(current->pid, &g_exit_status, 0);
		current = current->next;
	}
	ft_set_exit_status();
}

void	ft_clozi_pipes(t_commands *cmnd)
{
	t_commands	*current;

	current = cmnd;
	while (current)
	{
		close(current->pipefd[0]);
		close(current->pipefd[1]);
		current = current->next;
	}
}

void	ft_execute_more_than_one_cmd_with_pipes(t_data **data, t_commands *cmnd)
{
	t_commands	*current;
	int			i;

	i = 0;
	current = return_node_after_error(cmnd);
	if (!current->next)
		ft_execute_only_one_cmd_with_no_pipes(data, current);
	while (current)
	{
		if (i == 0)
			ft_execute_first_command(data, current);
		else if (!current->next)
			ft_execute_last_commaand(data, current);
		else
			ft_execute_middle_commandz(data, current);
		i++;
		current = current->next;
	}
	ft_clozi_pipes(cmnd);
	wait_for_processes(cmnd);
}

void	ft_execute_only_one_cmd_with_no_pipes(t_data **data, t_commands *cmnd)
{
	if (ft_check_cmd(data, cmnd, NULL))
	{
		if (ft_builtincdexpwithtpara(data, cmnd))
			return ;
		cmnd->pid = fork();
		if (cmnd->pid == 0)
		{
			signal(SIGQUIT, ft_sigints);
			signal(SIGINT, ft_sigints);
			dup2(cmnd->in_file, 0);
			dup2(cmnd->out_file, 1);
			if (ft_builtinechoexpwithpara(data, cmnd) == 0)
				g_exit_status = ft_execvee(cmnd->cmd, data);
			else
				exit(g_exit_status);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			ft_execute_parent_process(&cmnd);
			waitpid(cmnd->pid, &g_exit_status, 0);
			ft_set_exit_status();
		}
	}
}

void	ft_execute_the_cmd(t_data **data, t_commands *cmnd)
{
	if (!cmnd->next)
		ft_execute_only_one_cmd_with_no_pipes(data, cmnd);
	else
		ft_execute_more_than_one_cmd_with_pipes(data, cmnd);
	signal(SIGINT, ft_sigint);
}
