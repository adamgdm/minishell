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
    return (NULL);
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
            waitpid(frchita, NULL, 0);
        ft_freearr(environement);
        free(command);
    }    
}

void ft_execute_one_pipe(t_data **data, t_commands *cmnd)
{
    int frchita;
    int fd[2];
    char *command;
    char **environement;

    if (pipe(fd) == -1)
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
        else
        {
            dup2(fd[1], 1);
            close(fd[0]);
            if (execve(command, cmnd->cmd, environement) == -1);
            {
                perror("Execve: ");
                return ;
            }
        }
        waitpid(frchita, NULL, 0);
        ft_freearr(environement);
        free(command);
    }
    close(fd[1]);
    cmnd->in_file = fd[0];
}

void ft_execute_all(t_data **data, t_commands *cmnd)
{
    int **pipes;

    if (ft_execute(data, cmnd) == 1)
    {
        if (!cmnd->next)
            ft_executeonecmnd(data, cmnd);
        /*else
        {
            if (ft_count_how_many_pipes(cmnd) == 1)
                ft_execute_one_pipe(data, cmnd);
            else
            {
                pipes = ft_create_pipes(cmnd);
                ft_executepipes(data, cmnd, pipes);
                ft_free_pipes(pipes, cmnd);
            }
        }*/
    }
}