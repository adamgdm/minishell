#include "../minishell.h"

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

t_execcommand *ft_returndataforexec(t_data **data, t_commands *cmnd)
{
    t_execcommand *execcommand;

    execcommand = malloc(sizeof(t_execcommand));
    execcommand->command = ft_returnexistingcommandpath((*data)->env, cmnd->cmd[0]);
    execcommand->args = ft_changeelement(cmnd->cmd, 0, execcommand->command);
    execcommand->environement = ft_env_to_array((*data)->env);
    return (execcommand);
}

void ft_execvee(char **cmd, t_data **data)
{
    t_execcommand *excmd;
    t_commands *cmnd;

    cmnd = ft_createcommand(cmd);
    excmd = ft_returndataforexec(data, cmnd);
    execve(excmd->command, excmd->args, excmd->environement);
    ft_putstr_fd("Boubou_shell: ", 2);
    ft_putstr_fd(excmd->command, 2);
    ft_putstr_fd(": \n", 2);
    exit(127);
}

char **ft_changeelement(char **arr, int index, char *newelement)
{
    char **returnval;
    int i;

    i = 0;
    if (!newelement)
        return (arr);
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

void ft_freeexeccommand(t_execcommand *execcommand)
{
    if (execcommand->command)
    {
        free(execcommand->command);
        ft_freearr(execcommand->args);
    }
    ft_freearr(execcommand->environement);
    free(execcommand);
}
