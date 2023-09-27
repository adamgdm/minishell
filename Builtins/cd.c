#include "../minishell.h"

void    ft_cd(t_data **data, char *path, char *pwd)
{    
    if (!path)
    {
        path = fetchValue("HOME", (*data)->env);
        if (!path)
        {
            ft_putstr_fd("prettyshell: cd: HOME not set\n", 2);
            return ;
        }
        if (chdir(path) != 0)
            perror("cd");
        free (path);
    }
    else 
    {
        if (chdir(path) != 0)
            perror("cd");
    } 
    free(pwd);
}