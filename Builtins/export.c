#include "../minishell.h"

int ft_iseqin(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

void printenv(t_env *head, int fd) 
{
    t_env *current ;
    
    current = head;
    while (current) 
    {
        ft_putstr_fd("declare -x ", fd);
        ft_putstr_fd(current->str, fd);
        ft_putchar_fd('\n', fd);
        current = current->next;
    }
}

int ft_checkifruleexists(t_env *env, t_env *envnocmd, char *cmd)
{
    t_env *ee;
    t_env *ff;
    char *str;
    
    ee = env;
    ff = envnocmd;
    while (ee)
    {
        str = ft_strjoin(cmd, "=");
        if (!ft_strcmp(str, ee->str))
            return (1);
        free(str);
        ee = ee->next;
    }    
    while (ff)
    {
        str = ft_strdup(cmd);
        if (!ft_rulefinder(ff->str, str))
            return (1);
        ff = ff->next;
    }
    return (0);
}

char *ft_retiden(char *str)
{
    int i;
    char *ret;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    ret = ft_substr(str, 0, i);
    return (ret);
}

void    ft_unsetiden(t_env **env, t_env **envnocmd, char *iden)
{
    t_commands *cmnd;
    t_data *data;

    data = malloc(sizeof(t_data));
    data->env = (*env);
    data->envnoeq = (*envnocmd);
    cmnd = malloc(sizeof(t_commands));
    cmnd->cmd = malloc(sizeof(char *) * 3);
    cmnd->cmd[0] = ft_strdup("unset");
    cmnd->cmd[1] = ft_strdup(iden);
    cmnd->cmd[2] = NULL;
    ft_unset(&data, cmnd);
    free(cmnd->cmd[0]);
    free(cmnd->cmd[1]);
    free(cmnd->cmd);
}

char *ft_returnrule(t_env **env, char *cmd)
{
    t_env *head;
    char *iden;
    char *str;

    head = (*env);
    while (head)
    {
        iden = ft_retiden(cmd);
        str = ft_strjoin(iden, "=");
        if (!ft_strcmp(str, head->str))
        {
            free(iden);
            free(str);
            return (ft_strdup(head->str));
        }
        free(iden);
        free(str);
        head = head->next;
    }
    return (NULL);
}

int ft_checkexportvalididentifier(char *rts)
{
    int i;
    char *str;

    i = 0;
    if (!rts)
        return (0);
    str = ft_retiden(rts);
    if (str[i] != '_' && !ft_isalpha(str[i]))
        return (0);
    i++;
    while (str[i])
    {
        if (str[i] != '_' && !ft_isalnum(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int ft_checkrule(t_env **env, t_env **envnc, char *cmd)
{
    char *str;
    char *rule;

    str = ft_retiden(cmd);
    printf("%s\n", str);
    if (!ft_checkexportvalididentifier(str))
    {
        ft_putstr_fd("boubou_shell: export: `", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        free(str);
        return (0);
    }
    rule = ft_returnrule(envnc, str);
    if (!ft_iseqin(str) && ft_iseqin(rule))
    {
        free(str);
        return (0);
    }
    else
    {
        free(str);
        return (1);
    }
    return (0);
}

void    ft_export(t_env **env, t_env **envnocmd, t_commands *cmnd, int fd)
{
    t_env *head;
    int i;
    char *iden;

    i = 1;
    iden = NULL;
    head = (*envnocmd);
    if (!cmnd->cmd[i])    
        printenv(head, fd);
    else
    {
        while (cmnd->cmd[i])
        {
            if (ft_checkrule(env, envnocmd, cmnd->cmd[i]))
            {
                iden = ft_retiden(cmnd->cmd[i]);
                if (ft_checkifruleexists(*env, *envnocmd, iden))
                    ft_unsetiden(env, envnocmd, iden);
                if (ft_iseqin(cmnd->cmd[i]))
                {    
                    add_before_last_node(env, cmnd->cmd[i]);            
                    add_before_last_node(envnocmd,cmnd->cmd[i]);
                }
                else
                    add_before_last_node(envnocmd,cmnd->cmd[i]);
                free(iden);
            }
            i++;
        }
    }
}