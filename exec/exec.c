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
        {
        while (wait(NULL) != -1)
		    continue ;
        ft_freearr(environement);
        free(command);
        }    
    }
}

void ft_executeldakhel(t_data **data, t_commands *cmnd)
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
        dup2(cmnd->pipefd[0], 0);
        dup2(cmnd->pipefd[1], 1);
        close(cmnd->pipefd[0]);
        close(cmnd->pipefd[1]);
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
        close(cmnd->pipefd[0]);
        close(cmnd->pipefd[1]);
    }
    cmnd = cmnd->next;
    if (cmnd && cmnd->next)
        ft_executeldakhel(data, cmnd);
    else
        ft_executesecondcmnd(data, cmnd, NULL);
    ft_freearr(environement);
    free(command);
}


void ft_executesecondcmnd(t_data **data, t_commands *cmnd, int **pipes)
{
    int frchita;
    char **environement;
    char *command;
    (void)pipes;

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
        dup2(cmnd->pipefd[0], 0);
        dup2(cmnd->out_file, 1);
        close(cmnd->pipefd[0]);
        close(cmnd->pipefd[1]);
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
        close(cmnd->pipefd[0]);
        close(cmnd->pipefd[1]);
    }
    ft_freearr(environement);
    free(command);
}


void ft_execute_one_pipe(t_data **data, t_commands *cmnd, int **pipes)
{
    int frchita;
    char **environement;
    char *command;
    (void)pipes;

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
        dup2(cmnd->pipefd[1], 1);
        dup2(cmnd->in_file, 0);
        close(cmnd->pipefd[0]);
        close(cmnd->pipefd[1]);
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
        close(cmnd->pipefd[0]);
        close(cmnd->pipefd[1]);
    }
    cmnd = cmnd->next;
    if (!cmnd->next)
        ft_executesecondcmnd(data, cmnd, pipes);
    else
        ft_executeldakhel(data, cmnd);
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

void ft_execute_all(t_data **data, t_commands *cmnd)
{
    int forkita;
    int **pipes;

    forkita = fork();
    if (forkita == -1)
        perror("Fork");
    else if (forkita == 0)
    {
        if (ft_execute(data, cmnd) == 1)
        {
            if (!cmnd->next)
                ft_executeonecmnd(data, cmnd);
            else
            {
                ft_execute_one_pipe(data, cmnd, pipes);
            }
        }
    }
    ft_wait_last(forkita, 0);
}