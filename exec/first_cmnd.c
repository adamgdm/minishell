#include "../minishell.h"

void	ft_execute_child_mid_process(t_data **data, t_commands *cmnd)
{
    signal(SIGINT, ft_sigints);
    ft_set_up_io_mid_redirection(cmnd);
    ft_close_pipes(cmnd);
    if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
        ft_execvee(cmnd->cmd, data);
    else
        exit(1);
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

void	ft_execute_middle_commandz(t_data **data, t_commands *cmnd)
{
    if (ft_check_cmd(data, cmnd, NULL))
    {
        if (ft_builtings_cd_exit_unset_exportWithParameters(data, cmnd))
            return ;
        cmnd->pid = fork();
        if (cmnd->pid == 0)
            ft_execute_child_mid_process(data, cmnd);
        else
            ft_execute_parent_process(cmnd);
    }
}