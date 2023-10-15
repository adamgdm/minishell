/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fncts3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:27:42 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 02:29:39 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_ft_clozi_pipes_before(t_commands *cmnd)
{
	t_commands	*current;

	current = cmnd->previous;
	while (current)
	{
		close(current->pipefd[0]);
		close(current->pipefd[1]);
		current = current->previous;
	}
}

void	ft_ft_clozi_pipes(t_commands *cmnd)
{
	ft_ft_clozi_pipes_after(cmnd);
	ft_ft_clozi_pipes_before(cmnd);
}

void	ft_set_up_io_redirection(t_commands *cmnd)
{
	if (cmnd->out_file == 1 && cmnd->in_file == 0)
		dup2(cmnd->pipefd[0], 0);
	else
	{
		if (cmnd->out_file == 1 && cmnd->in_file != 0)
			dup2(cmnd->in_file, 0);
		else if (cmnd->out_file != 1 && cmnd->in_file == 0)
			dup2(cmnd->pipefd[0], 0);
		else
			dup2(cmnd->in_file, 0);
	}
	dup2(cmnd->out_file, 1);
}

void	ft_execute_child_process(t_data **data, t_commands *cmnd)
{
	signal(SIGINT, ft_sigints);
	signal(SIGQUIT, SIG_IGN);
	ft_set_up_io_redirection(cmnd);
	ft_ft_clozi_pipes(cmnd);
	if (ft_builtinechoexpwithpara(data, cmnd) == 0)
		ft_execvee(cmnd->cmd, data);
	else
		exit(g_exit_status);
}

void	ft_execute_last_commaand(t_data **data, t_commands *cmnd)
{
	if (ft_check_cmd(data, cmnd, NULL))
	{
		if (ft_builtincdexpwithtpara(data, cmnd))
			return ;
		cmnd->pid = fork();
		if (cmnd->pid == 0)
			ft_execute_child_process(data, cmnd);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			ft_execute_parent_process(&cmnd);
		}
	}
}
