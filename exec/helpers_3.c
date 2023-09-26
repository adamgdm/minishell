#include "../minishell.h"

int ft_which_line(char **envp, char *str)
{
    int i;
    int j;
    int k;
    
    i = 0;
    j = 0;
    k = 0;
    while (envp[i])
    {
        while (envp[i][j])
        {
            if (envp[i][j] == str[k])
            {   
                k++;
                if (k == ft_strlen(str) && j == k - 1)
                    return (i);
            }
            else
                k = 0;
            j++; 
        }
        j = 0;
        i++;
    }
    return (0);
}

char *ft_line_w_out_path(char *str, int len)
{
    int i;
    int j;
    char *line;

    i = 0;
    j = 0;
    line = (char *)malloc(sizeof(char) * len);
    if (!line)
        return (NULL);
    while (str[i] != ':')
        i++;
    while (j <= len)
    {
        line[j] = str[i];
        j++;
        i++;
    }
    return (line);
}

char **ft_find_path(char **envp, t_env *head)
{
    char *line;
    char **str;

    line = fetchValue("PATH", head);
    str = ft_split(line, ':');
    return (str);
}

char *ft_makethelist(char *cmd, char **path, t_env *head)
{
    char *command;
    char *hehe;
    int i;
    
    i = 0;
    while (path[i])
    {
        hehe = ft_strjoin(path[i], "/");
        command = ft_strjoin(hehe, cmd);
        free(hehe);
        if (access(command, 0) == 0)
			return (command);
        free(command);
        i++;
    }
    return (NULL);
}

void ft_execve(char **envp, char **cmnd, t_env *head)
{
    char *str;
    int i;

    if (fork())
    {
        str = ft_makethelist(cmnd[0], ft_find_path(envp, head), head);
        printf("%s\n",str);
        execve(str, cmnd, envp);
        perror("execve");
        //exit (1);
    }
    //free (str);
}