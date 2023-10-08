#include "../minishell.h"

int ft_builtings_cd_exit_unset_exportWithParameters(t_data **data, t_commands *cmnd)
{
    if (ft_doesmatch(cmnd->cmd[0], "cd"))
    {
        ft_cd(data, cmnd,cmnd->cmd[1]);
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

int ft_check_whether_builtins(char *cmd)
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

void ft_print_er(char *str, char *err, int exit_status)
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

int ft_check_if_directory(char *cmd)
{
    struct stat sb;

    if (ft_strchr(cmd, '/'))
    {
        if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
            ft_print_er(cmd, "Is a directory", 126);
        else
        {
            if (ft_rulefinder(cmd, ft_strdup("./")) && access(cmd, F_OK) == 0)
                ft_print_er(cmd, "Permission denied", 126);
            else if ((access(cmd, F_OK) == 0 || access(cmd, X_OK) == 0))
                ft_print_er(cmd, "Not a directory", 126);
            else
                ft_print_er(cmd, "No such file or directory", 127);
        }
    }
    else
        ft_print_er(cmd, "command not found", 127);
}

int ft_check_if_executable(char *str)
{
    if (ft_rulefinder(str, ft_strdup("./")) && 
        access(str, F_OK) == 0 && 
        access(str, X_OK) == 0)
    {
        return (1);        
    }
    return (0);
}

int ft_check_cmd(t_data **data, char *cmd)
{
    char *str;

    if (ft_check_whether_builtins(cmd))
        return (1);
    str = ft_returnexistingcommandpath((*data)->env, cmd);
    if (str)
    {
        free(str);
        return (1);
    }
    if (ft_check_if_executable(cmd))
        return (1);
    ft_check_if_directory(cmd);
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
    else if ((ft_doesmatch(cmnd->cmd[0], "pwd")))
    {
        ft_pwd(1);
        return (1);
    }
    return (0);
}

void ft_execute_first_command(t_data **data, t_commands *cmnd)
{
    int forkita;

    if (ft_check_cmd(data, cmnd->cmd[0]))
    {
        if (ft_builtings_cd_exit_unset_exportWithParameters(data, cmnd))
            return;
        forkita = fork();
        if (forkita == 0)
        {
            dup2(cmnd->in_file, 0);
            dup2(cmnd->pipefd[1], 1);
            close(cmnd->pipefd[0]);
            close(cmnd->pipefd[1]);
            if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
                ft_execvee(cmnd->cmd, data);
            else
                exit(0);
        }
        else
        {
            close(cmnd->pipefd[1]);
        }
    }
}

void ft_execute_middle_commandz(t_data **data, t_commands *cmnd)
{
    int forkita;

    if (ft_check_cmd(data, cmnd->cmd[0]))
    {
        if (ft_builtings_cd_exit_unset_exportWithParameters(data, cmnd))
            return;
        forkita = fork();
        if (forkita == 0)
        {
            dup2(cmnd->pipefd[0], 0);
            dup2(cmnd->pipefd[1], 1);
            close(cmnd->pipefd[0]);
            close(cmnd->pipefd[1]);
            if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
                ft_execvee(cmnd->cmd, data);
            else
                exit(0);
        }
        else
        {
            close(cmnd->pipefd[1]);
        }
    }
}

void ft_execute_last_commaand(t_data **data, t_commands *cmnd)
{
    int forkita;

    if (ft_check_cmd(data, cmnd->cmd[0]))
    {
        if (ft_builtings_cd_exit_unset_exportWithParameters(data, cmnd))
            return;
        forkita = fork();
        if (forkita == 0)
        {
            dup2(cmnd->pipefd[0], 0);
            dup2(cmnd->out_file, 1);
            close(cmnd->pipefd[0]);
            close(cmnd->pipefd[1]);
            if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
                ft_execvee(cmnd->cmd, data);
            else
                exit(g_exit_status);
        }
        else
        {
            close(cmnd->pipefd[1]);
        }
    }
}
void ft_execute_more_than_one_cmd_with_pipes(t_data **data, t_commands *cmnd)
{
    t_commands *current;
    int forkita;
    int i;
    int check;

    i = 0;
    current = cmnd;
    while (current)
    {
        // if (ft_check_cmd(data ,current->cmd[0]))
        // {

        if (i == 0)
            ft_execute_first_command(data, current);
        else if (!current->next)
        {
            ft_execute_last_commaand(data, current);
        }
        else
            ft_execute_middle_commandz(data, current);
        // }
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

void ft_execute_only_one_cmd_with_no_pipes(t_data **data, t_commands *cmnd)
{
    int forkita;

    if (ft_check_cmd(data, cmnd->cmd[0]))
    {
        if (ft_builtings_cd_exit_unset_exportWithParameters(data, cmnd))
            return;
        forkita = fork();
        if (forkita == 0)
        {
            dup2(cmnd->in_file, 0);
            dup2(cmnd->out_file, 1);
            if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
                ft_execvee(cmnd->cmd, data);
            else
                exit(g_exit_status);
        }
        else
        {
            waitpid(forkita, NULL, 0);
        }
    }
}

void ft_execute_the_cmd(t_data **data, t_commands *cmnd)
{
    if (!cmnd->next)
        ft_execute_only_one_cmd_with_no_pipes(data, cmnd);
    else
    {
        ft_execute_more_than_one_cmd_with_pipes(data, cmnd);
    }
}