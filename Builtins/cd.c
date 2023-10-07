#include "../minishell.h"

void ft_unsetandexport(t_data **data, char *rts)
{
    char **cmd;
    char *str;
    t_commands *comond;
    char *pwd;

    pwd = ft_returnpwd();
    comond = ft_createcommand(ft_split("unset OLDPWD", ' '));
    ft_unset(data, comond);
    ft_freecmd(comond);
    str = ft_strjoin("export OLDPWD=", rts);
    cmd = ft_split(str, ' ');
    ft_export(data, cmd);
    free(str);
    ft_freearr(cmd);
    comond = ft_createcommand(ft_split("unset PWD", ' '));
    ft_unset(data, comond);
    ft_freecmd(comond);
    str = ft_strjoin("export PWD=", pwd);
    cmd = ft_split(str, ' ');
    ft_export(data, cmd);
    free(str);
    free(pwd);
    ft_freearr(cmd);
}

void    ft_cd(t_data **data, char *path)
{    
    char *pwd;
    
    pwd = ft_returnpwd();
    if (!path)
    {
        path = fetchValue("HOME", (*data)->env);
        if (!path)
        {
            ft_putstr_fd("Boubou_shell: cd: HOME not set\n", 2);
            return ;
        }
        if (chdir(path) != 0)
        {
            perror("cd");
            free(pwd);
            free(path);
            return ;
        }    
        free (path);
    }
    else 
    {
        if (chdir(path) != 0)
        {
            perror("cd");
            free(pwd);
        }
    }
    ft_unsetandexport(data, pwd);
    free(pwd);
}