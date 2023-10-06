#include "../minishell.h"

char **ft_env_to_array(t_env *env)
{
    char **envp;
    int i;
    t_env *tmp;

    i = 0;
    tmp = env;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    envp = malloc(sizeof(char *) * (i + 1));
    if (!envp)
        return (NULL);
    i = 0;
    while (env)
    {
        envp[i] = ft_strdup(env->str);
        i++;
        env = env->next;
    }
    envp[i] = NULL;
    return (envp);
}

char *ft_returnexistingcommandpath(t_env *env, char *cmnd)
{
    char *path;
    char *command;
    char **paths;
    int i;
    char *tmp;

    i = 0;
    path = fetchValue("PATH", env);
    paths = ft_split(path, ':');
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        command = ft_strjoin(tmp, cmnd);
        free(tmp);
        if (access(command, F_OK) == 0)
        {
            free(path);
            ft_freearr(paths);
            return (command);
        }
        free(command);
        i++;
    }
    free(path);
    ft_freearr(paths);
    return (cmnd);
}



void ft_executeonecmnd(t_data **data, t_commands *cmnd)
{
    char *command;
    char **environement;
    int frchita;

    if (cmnd->in_file == -1 && cmnd->out_file == -1)
        return ;
    command = ft_returnexistingcommandpath((*data)->env, cmnd->cmd[0]);
    if (command)
    {
        environement = ft_env_to_array((*data)->env);
        if (!environement)
        {
            free(command);
            return ;
        }
        frchita = fork();
        if (frchita == -1)
            perror("Fork");
        else if (frchita == 0)
        {    
            dup2(cmnd->in_file, 0);
            dup2(cmnd->out_file, 1);
            if (execve(command, cmnd->cmd, environement) == -1)
            {
                perror("Execve");
                return ;
            }
        }
        else
        {
        while (wait(NULL) != -1)
		    continue ;
        ft_freearr(environement);
        free(command);
        }    
    }
}

int ft_count_how_many_pipes(t_commands *cmnd)
{
    int i;

    i = 0;
    while (cmnd)
    {
        if (cmnd)
            i++;
        cmnd = cmnd->next;
    }
    return (i);
}

void	ft_wait_last(int pid, int status)
{
	waitpid(pid, &status, 0);
	/*if (WIFEXITED(status))
		g_exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_stat = 128 + WTERMSIG(status);*/
}

char **ft_changeelement(char **arr, int index, char *newelement)
{
    char **returnval;
    int i;

    i = 0;
    returnval = malloc(sizeof(char *) * (ft_count(arr) + 1));
    while (arr[i])
    {
        if (i == index)
            returnval[i] = ft_strdup(newelement);
        else
            returnval[i] = ft_strdup(arr[i]);
        i++;
    }
    returnval[i] = NULL;
    return (returnval);
}

t_execcommand *ft_returndataforexec(t_data **data, t_commands *cmnd)
{
    t_execcommand *execcommand;

    execcommand = malloc(sizeof(t_execcommand));
    execcommand->command = ft_returnexistingcommandpath((*data)->env, cmnd->cmd[0]);
    execcommand->args = ft_changeelement(cmnd->cmd, 0, execcommand->command);
    execcommand->environement = ft_env_to_array((*data)->env);
    return (execcommand);
}

void ft_freeexeccommand(t_execcommand *execcommand)
{
    free(execcommand->command);
    ft_freearr(execcommand->args);
    ft_freearr(execcommand->environement);
    free(execcommand);
}

void ft_execute_one(t_data **data, t_commands *cmnd)
{
    int forkita;
    t_execcommand *execmd;

    if (cmnd->in_file == -1 && cmnd->out_file == -1)
        return ;
    else
    {
        forkita = ft_check_builtins(cmnd, cmnd->cmd[0]);
        if (forkita)
            ft_executebultin(data, cmnd, forkita);
        else
        {
            forkita = fork();
            if (forkita == -1)
                perror("Fork");
            else if (forkita == 0)
            {
                dup2(cmnd->in_file, 0);
                dup2(cmnd->out_file, 1);
                execmd = ft_returndataforexec(data, cmnd);
                if (execve(execmd->command, execmd->args, execmd->environement) == -1)
                {
                    perror("Execve");
                    return ;
                }
                ft_freeexeccommand(execmd);
            }
            else
            {
                waitpid(forkita, NULL, 0);
                close(cmnd->pipefd[0]);
                close(cmnd->pipefd[1]);
            }
        }
    }
}

void ft_execute_one_pip(t_data **data, t_commands *cmnd)
{
    int forkita;
    t_execcommand *execmd;

    if (cmnd->in_file == -1 && cmnd->out_file == -1)
        return ;
    else
    {
        forkita = ft_check_builtins(cmnd, cmnd->cmd[0]);
        if (forkita)
            ft_executebultin(data, cmnd, forkita);
        else
        {
            forkita = fork();
            if (forkita == -1)
                perror("Fork");
            else if (forkita == 0)
            {
                dup2(cmnd->in_file, 0);
                dup2(cmnd->pipefd[1], 1);
                execmd = ft_returndataforexec(data, cmnd);
                if (execve(execmd->command, execmd->args, execmd->environement) == -1)
                {
                    perror("Execve");
                    return ;
                }
                ft_freeexeccommand(execmd);
            }
            else
            {
                waitpid(forkita, NULL, 0);
                close(cmnd->pipefd[0]);
                close(cmnd->pipefd[1]);
            }
        }
        cmnd = cmnd->next;
        if (cmnd && cmnd->next)
            ft_execute_middle_commands(data, cmnd);
        else
            ft_execute_last_command(data, cmnd);
    }
}

void ft_execute_middle_commands(t_data **data, t_commands *cmnd)
{
    int forkita;
    t_execcommand *execmd;

    if (cmnd->in_file == -1 && cmnd->out_file == -1)
        return ;
    else
    {
        forkita = ft_check_builtins(cmnd, cmnd->cmd[0]);
        if (forkita)
            ft_executebultin(data, cmnd, forkita);
        else
        {
            forkita = fork();
            if (forkita == -1)
                perror("Fork");
            else if (forkita == 0)
            {
                dup2(cmnd->pipefd[0], 0);
                dup2(cmnd->pipefd[1], 1);
                execmd = ft_returndataforexec(data, cmnd);
                if (execve(execmd->command, execmd->args, execmd->environement) == -1)
                {
                    perror("Execve");
                    return ;
                }
                ft_freeexeccommand(execmd);
            }
            else
            {
                waitpid(forkita, NULL, 0);
                close(cmnd->pipefd[0]);
                close(cmnd->pipefd[1]);
            }
        }
        cmnd = cmnd->next;
        if (cmnd && cmnd->next)
            ft_execute_middle_commands(data, cmnd);
        else
            ft_execute_last_command(data, cmnd);
    }
}

void ft_execute_last_command(t_data **data, t_commands *cmnd)
{
    int forkita;
    t_execcommand *execmd;

    forkita = 0;
    if (cmnd->in_file == -1 && cmnd->out_file == -1)
        return ;
    else
    {
        forkita = ft_check_builtins(cmnd, cmnd->cmd[0]);
        if (forkita)
            ft_executebultin(data, cmnd, forkita);
        else
        {
            forkita = fork();
            if (forkita == -1)
                perror("Fork");
            else if (forkita == 0)
            {
                dup2(cmnd->pipefd[0], 0);
                dup2(cmnd->out_file, 1);
                execmd = ft_returndataforexec(data, cmnd);
                if (execve(execmd->command, execmd->args, execmd->environement) == -1)
                {
                    perror("Execve");
                    return ;
                }
                ft_freeexeccommand(execmd);
            }
            else
            {
                waitpid(forkita, NULL, 0);
                close(cmnd->pipefd[0]);
                close(cmnd->pipefd[1]);
            }
        }
    }
}

void ft_executebultin(t_data **data, t_commands *cmnd, int forkita)
{
    int forchita = 0;
    
    forchita = fork();
    if (forchita == -1)
        perror("Fork");
    else if (forchita == 0)
    {
        if (cmnd->next)
            dup2(cmnd->pipefd[1], 1);
        else
            dup2(cmnd->out_file, 1);
        if (forkita == 1)
            ft_execute_builtins(data, cmnd);
        else if (forkita == 2)
            ft_execute_builtins2(data, cmnd);
        wait(NULL);
        exit(0);
    }
    else
    {
        waitpid(forchita, NULL, 0);
        close(cmnd->pipefd[0]);
        close(cmnd->pipefd[1]);
    }
}

void ft_execute_builtins(t_data **data, t_commands *cmnd)
{
    if (cmnd->next)
        dup2(cmnd->pipefd[1], 1);
    if (!ft_strcmp(cmnd->cmd[0], "echo"))
        ft_echo(cmnd->cmd, 1);
    else if (!ft_strcmp(cmnd->cmd[0], "pwd"))
        ft_pwd(1);
    else if (!ft_strcmp(cmnd->cmd[0], "export"))
        ft_export(data, cmnd->cmd, 1);
    else if (!ft_strcmp(cmnd->cmd[0], "env"))
        ft_env(data, 1);
}

void ft_execute_builtins2(t_data **data, t_commands *cmnd)
{
    char *pwd;

    pwd = ft_returnrule((*data)->env, "OLDPWD");
    if (!ft_strcmp(cmnd->cmd[0], "cd"))
        ft_cd(data , pwd);
    else if (!ft_strcmp(cmnd->cmd[0], "unset"))
        ft_unset(data, cmnd);
    else if (!ft_strcmp(cmnd->cmd[0], "exit"))
        ft_exit((data), cmnd);
    else if (!ft_strcmp(cmnd->cmd[0], "export"))
        ft_export(data, cmnd->cmd, 1);
    free(pwd);
}

int ft_check_builtins(t_commands *cmndd,char *cmnd)
{
    if (!ft_strcmp(cmnd, "echo"))
        return (1);
    else if (!ft_strcmp(cmnd, "cd"))
        return (2);
    else if (!ft_strcmp(cmnd, "pwd"))
        return (1);
    else if (!ft_strcmp(cmnd, "export") && cmndd->cmd[1])
        return (2);
    else if (!ft_strcmp(cmnd, "export") && !cmndd->cmd[1])
        return (1);
    else if (!ft_strcmp(cmnd, "unset"))
        return (2);
    else if (!ft_strcmp(cmnd, "env"))
        return (1);
    else if (!ft_strcmp(cmnd, "exit"))
        return (2);
    else
        return (0);
}

void ft_execute_all(t_data **data, t_commands *cmnd)
{
    int forkita;
    int **pipes;

      if (!cmnd->next)
            ft_execute_one(data, cmnd);
        else
            ft_execute_one_pip(data, cmnd);
    }

