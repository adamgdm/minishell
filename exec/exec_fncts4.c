/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fncts4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:28:31 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:19:19 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtinechoexpwithpara(t_data **data, t_commands *cmnd)
{
	if (ft_doesmatch(cmnd->cmd[0], "echo"))
	{
		ft_echo(cmnd->cmd, 1);
		return (1);
	}
	else if (ft_doesmatch(cmnd->cmd[0], "env"))
	{
		ft_env_pre(cmnd->cmd[1], data, 1);
		return (1);
	}
	else if ((ft_doesmatch(cmnd->cmd[0], "export") && !cmnd->cmd[1]))
	{
		ft_export(data, cmnd->cmd, 1, 1);
		return (1);
	}
	else if ((ft_doesmatch(cmnd->cmd[0], "pwd")))
	{
		ft_pwd_pre(cmnd->cmd[1], data, 1);
		return (1);
	}
	return (0);
}

void	ft_execute_parent_process(t_commands **cmnd)
{
	t_commands	*current;

	current = (*cmnd);
	if (current->pid == -1)
	{
		perror("fork");
		g_exit_status = 1;
	}
	close(current->pipefd[1]);
}

void	ft_efn(t_commands **comnd, t_commands *current)
{
	t_commands	*cmnd;

	cmnd = (*comnd);
	signal(SIGINT, ft_sigints);
	dup2(cmnd->in_file, 0);
	if (cmnd->out_file == 1)
		dup2(cmnd->pipefd[1], 1);
	else
		dup2(cmnd->out_file, 1);
	close(cmnd->pipefd[0]);
	close(cmnd->pipefd[1]);
	current = cmnd->next;
	while (current)
	{
		close(current->pipefd[0]);
		close(current->pipefd[1]);
		current = current->next;
	}
	current = cmnd->previous;
	while (current)
	{
		close(current->pipefd[0]);
		close(current->pipefd[1]);
		current = current->previous;
	}
}

void	ft_execute_first_command(t_data **data, t_commands *cmnd)
{
	if (ft_check_cmd(data, cmnd, NULL))
	{
		if (ft_builtincdexpwithtpara(data, cmnd))
			return ;
		cmnd->pid = fork();
		if (cmnd->pid == 0)
		{
			ft_efn(&cmnd, NULL);
			if (ft_builtinechoexpwithpara(data, cmnd) == 0)
				ft_execvee(cmnd->cmd, data);
			else
				exit(0);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			ft_execute_parent_process(&cmnd);
		}
	}
}

void	ft_ft_clozi_pipes_after(t_commands *cmnd)
{
	t_commands	*current;

	current = cmnd->next;
	while (current)
	{
		close(current->pipefd[0]);
		close(current->pipefd[1]);
		current = current->next;
	}
}
