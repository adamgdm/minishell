/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:00:52 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/13 08:44:58 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtings_cd_exit_unset_exportwithparameters(t_data **data,
													t_commands *cmnd)
{
	if (ft_doesmatch(cmnd->cmd[0], "cd"))
	{
		ft_cd(data, cmnd, cmnd->cmd[1]);
		return (1);
	}
	else if (ft_doesmatch(cmnd->cmd[0], "exit"))
	{
		ft_exit(data, cmnd);
		return (1);
	}
	else if (ft_doesmatch(cmnd->cmd[0], "unset"))
	{
		ft_unset(data, cmnd);
		return (1);
	}
	else if ((ft_doesmatch(cmnd->cmd[0], "export") && cmnd->cmd[1]))
	{
		ft_export(data, cmnd->cmd, 1, cmnd->out_file);
		return (1);
	}
	return (0);
}

int	ft_check_whether_builtins(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

void	ft_print_er(char *str, char *err, int exit_status)
{
	ft_putstr_fd("Boubou_shell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (err)
		ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = exit_status;
}

char	*return_wsback(char *str)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			j = i;
		i++;
	}
	new = ft_substr(str, 0, j);
	return (new);
}

void	ft_handle_path_existance(t_data **data, char *cmd)
{
	if (ft_ruleexist(data, "PATH"))
		ft_print_er(cmd, "command not found", 127);
	else
		ft_print_er(cmd, "No such file or directory", 127);
}

void	ft_check_if_directory(t_data **data, char *cmd, char *str)
{
	struct stat	sb;

	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			ft_print_er(cmd, "Is a directory", 126);
		}
		else
		{
			if (ft_rulefinder(cmd, ft_strdup("./")) && access(cmd, F_OK) == 0)
				ft_print_er(cmd, "Permission denied", 126);
			else if ((access(cmd, F_OK) == 0 || access(cmd, X_OK) == 0)
				|| (access(str, F_OK) == 0 || access(str, X_OK) == 0))
				ft_print_er(cmd, "Not a directory", 126);
			else
				ft_print_er(cmd, "No such file or directory", 127);
		}
	}
	else
		ft_handle_path_existance(data, cmd);
	if (str)
		free(str);
}

int	ft_check_if_executable(char *str)
{
	if (ft_rulefinder(str, ft_strdup("./"))
		&& access(str, F_OK) == 0
		&& access(str, X_OK) == 0)
	{
		return (1);
	}
	return (0);
}

int	ft_check_cmd(t_data **data, t_commands *comond, char *cmd)
{
	char	*str;

	if (!comond->cmd || !comond->cmd[0])
		return (0);
	cmd = comond->cmd[0];
	if (comond->error_exist)
	{
		g_exit_status = 1;
		return (0);
	}
	if (ft_check_whether_builtins(cmd))
		return (1);
	str = ft_rtexpath((*data)->env, cmd, 0, NULL);
	if (str)
	{
		free(str);
		return (1);
	}
	if (ft_check_if_executable(cmd))
		return (1);
	ft_check_if_directory(data, cmd, return_wsback(cmd));
	return (0);
}

int	ft_builtings_echo_env_exportwithparameters(t_data **data, t_commands *cmnd)
{
	if (ft_doesmatch(cmnd->cmd[0], "echo"))
	{
		ft_echo(cmnd->cmd, 1);
		return (1);
	}
	else if (ft_doesmatch(cmnd->cmd[0], "env"))
	{
		ft_env(data, 1);
		return (1);
	}
	else if ((ft_doesmatch(cmnd->cmd[0], "export") && !cmnd->cmd[1]))
	{
		ft_export(data, cmnd->cmd, 1, 1);
		return (1);
	}
	else if ((ft_doesmatch(cmnd->cmd[0], "pwd")))
	{
		ft_pwd(data, 1);
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

void	ft_efn(t_data **data, t_commands **comnd, t_commands *current)
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
	int			forkita;
	t_commands	*current;

	if (ft_check_cmd(data, cmnd, NULL))
	{
		if (ft_builtings_cd_exit_unset_exportwithparameters(data, cmnd))
			return ;
		cmnd->pid = fork();
		if (cmnd->pid == 0)
		{
			ft_efn(data, &cmnd, NULL);
			if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
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
    ft_set_up_io_redirection(cmnd);
    ft_ft_clozi_pipes(cmnd);
    if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
        ft_execvee(cmnd->cmd, data);
    else
        exit(g_exit_status);
}

void	ft_execute_last_commaand(t_data **data, t_commands *cmnd)
{
    if (ft_check_cmd(data, cmnd, NULL))
    {
        if (ft_builtings_cd_exit_unset_exportwithparameters(data, cmnd))
            return ;
        cmnd->pid = fork();
        if (cmnd->pid == 0)
            ft_execute_child_process(data, cmnd);
        else
		{
    		signal(SIGINT, SIG_IGN);
            ft_execute_parent_process(&cmnd);
		}
	}
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
    ft_set_up_io_mid_redirection(cmnd);
    ft_ft_clozi_pipes(cmnd);
    if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
        ft_execvee(cmnd->cmd, data);
    else
        exit(0);
}

void	ft_execute_middle_commandz(t_data **data, t_commands *cmnd)
{
    if (ft_check_cmd(data, cmnd, NULL))
    {
        if (ft_builtings_cd_exit_unset_exportwithparameters(data, cmnd))
            return ;
        cmnd->pid = fork();
        if (cmnd->pid == 0)
            ft_execute_child_mid_process(data, cmnd);
        else
		{
    		signal(SIGINT, SIG_IGN);
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

void	wait_for_processes(t_commands *cmnd)
{
    t_commands	*current;

    current = cmnd;
    while (current)
    {
        waitpid(-1, NULL, 0);
        current = current->next;
    }
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
	int	forkita;

	if (ft_check_cmd(data, cmnd, NULL))
	{
		if (ft_builtings_cd_exit_unset_exportwithparameters(data, cmnd))
			return ;
		cmnd->pid = fork();
		if (cmnd->pid == 0)
		{
			signal(SIGINT, ft_sigints);
			dup2(cmnd->in_file, 0);
			dup2(cmnd->out_file, 1);
			if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
				ft_execvee(cmnd->cmd, data);
			else
				exit(0);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			ft_execute_parent_process(&cmnd);
			waitpid(-1, NULL, 0);
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
