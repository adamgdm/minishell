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

void ft_executesecondcmnd(t_data **data, t_commands *cmnd, int **pipes)
{
    int frchita;
    char **environement;
    char *command;

    command = ft_returnexistingcommandpath((*data)->env, cmnd->cmd[0]);
    if (!command)
        return ;
    environement = ft_env_to_array((*data)->env);
    if (!environement)
    {
        free(command);
        return ;
    }
    printf("l3ezz\n");
    frchita = fork();
    if (frchita == -1)
        perror("Fork");
    else if (frchita == 0)
    {
        dup2(pipes[0][0], 0);
        dup2(cmnd->next->out_file, 1);
        close(pipes[0][0]);
        close(pipes[0][1]);
        if (execve(command, cmnd->cmd, environement) == -1)
        {
            perror("Execve");
            return ;
        }
    }
    else
    {
        waitpid(frchita, NULL, 0);
        close(pipes[0][1]);
        close(pipes[0][0]);
    }
    ft_freearr(environement);
    free(command);
}


void ft_execute_one_pipe(t_data **data, t_commands *cmnd, int **pipes)
{
    int frchita;
    char **environement;
    char *command;

    command = ft_returnexistingcommandpath((*data)->env, cmnd->cmd[0]);
    if (!command)
        return ;
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
        dup2(pipes[0][1], 1);
        dup2(cmnd->in_file, 0);
        close(pipes[0][0]);
        close(pipes[0][1]);
        if (execve(command, cmnd->cmd, environement) == -1)
        {
            perror("Execve");
            return ;
        }
    }
    else
    {
        waitpid(frchita, NULL, 0);
        close(pipes[0][1]);
        close(pipes[0][0]);
    }
    ft_executesecondcmnd(data, cmnd->next, pipes);
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

void ft_execute_all(t_data **data, t_commands *cmnd)
{
    int **pipes;

    if (ft_execute(data, cmnd) == 1)
    {
        if (!cmnd->next)
            ft_executeonecmnd(data, cmnd);
        else
        {
            pipes = ft_create_pipes(cmnd);
            if (ft_count_how_many_pipes(cmnd) == 2)
            {
                ft_execute_one_pipe(data, cmnd, pipes);
            }
            else
            {
                printf("L3ezz\n");
                //ft_executepipes(data, cmnd, pipes);
                ft_free_pipes(pipes, cmnd, ft_count_how_many_pipes(cmnd) - 1);
            }
        }
    }
}