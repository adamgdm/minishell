#include "../minishell.h"

void ft_free_cd_stuff(char *str, char *str2, char **str3)
{
    if (str)
        free(str);
    if (str2)
        free(str2);
    if (str3)
        ft_freearr(str3);
}

void ft_unsetandexport(t_data **data, char *rts, char *pwd, char *str)
{
    char **cmd;
    t_commands *comond;

    pwd = ft_returnpwd();
    if (ft_ruleexist(data, "OLDPWD"))
    {
        comond = ft_createcommand(ft_split("unset OLDPWD", ' '));
        ft_unset(data, comond);
        ft_freecmd(comond);
        str = ft_strjoin("export OLDPWD=", rts);
        cmd = ft_split(str, ' ');
        ft_export(data, cmd);
        ft_free_cd_stuff(str, NULL, cmd);
    }
    if (ft_ruleexist(data, "PWD"))
    {
        comond = ft_createcommand(ft_split("unset PWD", ' '));
        ft_unset(data, comond);
        ft_freecmd(comond);
        str = ft_strjoin("export PWD=", pwd);
        cmd = ft_split(str, ' ');
        ft_export(data, cmd);
        ft_free_cd_stuff(str, pwd, cmd);
    }
}

int ft_chdir_error_print(char *path)
{
    perror("Boubou_shell: cd");
    free(path);
    return (g_exit_status = 1);;
}

int ft_handle_cd_errors(t_data **data, t_commands *cmnd, char *path)
{
    if (cmnd->cmd[1] && cmnd->cmd[2])
    {
        ft_putstr_fd("Boubou_shell: cd: too many arguments\n", 2);
        return (g_exit_status = 1);
    }
    if (!path)
    {
        path = fetchValue("HOME", (*data)->env);
        if (!path)
        {
            ft_putstr_fd("Boubou_shell: cd: HOME not set\n", 2);
            return (g_exit_status = 1);
        }
        if (chdir(path) != 0)
            return (ft_chdir_error_print(path));
        else
        {
            free(path);
            g_exit_status = 0;
            return (1);
        }
        free(path);
    }
    return (0);
}

//the reason why whenever this command is executed with a non Null path, it prints 2 new lines because of the free(pwd) in ft_unsetandexport at the line 

void ft_cd(t_data **data, t_commands *comond, char *path)
{
    char *pwd;

    pwd = ft_returnpwd();
    if (ft_handle_cd_errors(data, comond, path))
    {
        free(pwd);
        return;
    }
    else
    {
        if (chdir(path) != 0)
        {
            perror("Boubou_shell: cd");
            free(pwd);
            g_exit_status = 1;
            return;
        }
    }
    ft_unsetandexport(data, pwd, NULL, NULL);
    free(pwd);
    g_exit_status = 0;
}