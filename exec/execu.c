#include "../minishell.h"

int ft_builtings_cd_exit_unset_exportWithParameters(t_data **data, t_commands *cmnd)
{
    if (ft_doesmatch(cmnd->cmd[0], "cd"))
    {
        ft_cd(data, cmnd->cmd[1]);
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
        ft_export(data, cmnd->cmd);
        return (1);
    }
    return (0);
}

int ft_builtings_echo_env_exportwithparameters(t_data **data, t_commands *cmnd)
{
    if (ft_doesmatch(cmnd->cmd[0], "echo"))
    {
        ft_echo(cmnd->cmd);
        return (1);
    }
    else if (ft_doesmatch(cmnd->cmd[0], "env"))
    {
        ft_env(data);
        return (1);
    }
    else if ((ft_doesmatch(cmnd->cmd[0], "export") && !cmnd->cmd[1]))
    {
        ft_export(data, cmnd->cmd);
        return (1);
    }
    return (0);
}

void ft_execute_only_one_cmd_with_no_pipes(t_data **data, t_commands *cmnd)
{
    int forkita;

    if (ft_builtings_cd_exit_unset_exportWithParameters(data, cmnd))
    {
        printf("HHH\n");    
        return ;
    }
    forkita = fork();
    if (forkita == 0)
    {
        dup2(cmnd->in_file, 0);
        dup2(cmnd->out_file, 1);
        if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
            ft_execvee(cmnd->cmd, data);
        else
            exit(0);

    }
    else
    {
        waitpid(forkita, NULL, 0);
    }
}

void ft_execute_first_command(t_data **data, t_commands *cmnd)
{
    int forkita;

    forkita = fork();
    if (forkita == 0)
    {
        dup2(cmnd->in_file, 0);
        dup2(cmnd->pipefd[1], 1);
        close(cmnd->pipefd[0]);
        close(cmnd->pipefd[1]);
        if (!ft_builtings_cd_exit_unset_exportWithParameters(data, cmnd) == 0)
        {   
            if (!ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
            {
                ft_execvee(cmnd->cmd, data);
            }
            ft_execvee(cmnd->cmd, data);
        }
    }
    else
    {
        close(cmnd->pipefd[1]);
    }
}

void ft_execute_middle_commandz(t_data **data, t_commands *cmnd)
{
    int forkita;

    forkita = fork();
    if (forkita == 0)
    {
        dup2(cmnd->pipefd[0], 0);
        dup2(cmnd->pipefd[1], 1);
        close(cmnd->pipefd[0]);
        close(cmnd->pipefd[1]);
        //ft_execute_builtins(data, cmnd);
       // ft_execute_builtins2(data, cmnd);
        ft_execvee(cmnd->cmd, data);
    }
    else
    {
        close(cmnd->pipefd[1]);
    }
}

void ft_execute_last_commaand(t_data **data, t_commands *cmnd)
{
    int forkita;

    forkita = fork();
    signal(SIGINT, ft_sigint);
    if (forkita == 0)
    {
        dup2(cmnd->pipefd[0], 0);
        dup2(cmnd->out_file, 1);
        close(cmnd->pipefd[0]);
        close(cmnd->pipefd[1]);
        //ft_execute_builtins(data, cmnd);
       // ft_execute_builtins2(data, cmnd);
        ft_execvee(cmnd->cmd, data);
    }
    else
    {
        close(cmnd->pipefd[0]);
    }
}

void ft_execute_more_than_one_cmd_with_pipes(t_data **data, t_commands *cmnd)
{
    t_commands *current;
    int forkita;
    int i;

    i = 0;
    current = cmnd;
    while (current)
    {
        if (i == 0)
        {
            ft_execute_first_command(data, current);
        }
        else if (!current->next)
        {
            ft_execute_last_commaand(data, current);
        }
        else
        {
            ft_execute_middle_commandz(data, current);
        }
        i++;
        current = current->next;
    }
    i = 0;
    current = cmnd;
    while (current)
    {
        close(current->pipefd[0]);
        close(current->pipefd[1]);
        current = current->next;
    }
    current = cmnd;
    while (current)
    {
        waitpid(-1, NULL, 0);
        current = current->next;
    }
}

void    ft_execute_the_cmd(t_data **data, t_commands *cmnd)
{
    if (!cmnd->next)
        ft_execute_only_one_cmd_with_no_pipes(data, cmnd);
    else
    {
        ft_execute_more_than_one_cmd_with_pipes(data, cmnd);
    }
}