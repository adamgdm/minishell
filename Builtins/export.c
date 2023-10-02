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

char *ft_retidenplus(char *str)
{
    int i;
    char *ret;

    i = 0;
    while (str[i] && str[i] != '=' && str[i] != '+')
        i++;
    ret = ft_substr(str, 0, i);
    return (ret);
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

int ft_strcmpwithoutnull(char *str, char *rts)
{
    int i;

    i = 0;
    while (str[i] && rts[i])
    {
        if (str[i] != rts[i])
            return (0);
        i++;
    }
    return (1);
}

int ft_checkifruleexists(t_env *env, t_env *envnocmd, char *cmd)
{
    t_env *ee;
    t_env *ff;
    char *str;
    int i;
    int j;
    
    i = 0;
    j = 0;
    ee = env;
    ff = envnocmd;
    while (ee)
    {
        str = ft_strjoin(ft_retiden(cmd), "=");
        if (ft_strcmpwithoutnull(ee->str, str))
        {
          //  printf("a= %s\n", ee->str);
            i = 1;
            break ;
        }
        free(str);
        ee = ee->next;
    }    
    while (ff)
    {
        str = ft_retiden(cmd);
        if (!ft_strcmp(ff->str, str))
        {
            j = 1;
            break ;
        }
        free(str);
        ff = ff->next;
    }
   // printf("i = %d\n", i);
   // printf("j = %d\n", j);
   // printf("k = %d\n", ft_iseqin(cmd));
    if (i == 0 && j == 1 && ft_iseqin(cmd))
        return (1);
    else if (i == 1 && j == 1 && ft_iseqin(cmd))
        return (1);
    else if (i == 1 && j == 0 && ft_iseqin(cmd))
        return (1);
    else if (i == 0 && j == 0 && ft_iseqin(cmd))
        return (0);
    else if (i == 0 && j == 1 && !ft_iseqin(cmd))
        return (1);
    else if (i == 1 && j == 1 && !ft_iseqin(cmd))
        return (0);
    else if (i == 1 && j == 0 && !ft_iseqin(cmd))
        return (0);
    else if (i == 0 && j == 0 && !ft_iseqin(cmd))
        return (0);
    return (0);
}



void    ft_unsetiden(t_env **env, t_env **envnocmd, char *iden)
{
    t_commands *cmnd;
    t_data *data;

 //   printf("rule : asl\n");
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
    t_env *ff;
    char *iden;
    char *str;

    ff = (*env);
    while (ff)
    {
        str = ft_retiden(cmd);
        if (ft_strcmpwithoutnull(ff->str, str))
        {
            free(str);
            return(ft_strdup(ff->str));
        }
        free(str);
        ff = ff->next;
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

    str = ft_retidenplus(cmd);
    printf("%s\n", str);
    if (!ft_checkexportvalididentifier(str))
    {
        printf("ft_checkrule = %d\n", ft_checkexportvalididentifier(str));
        ft_putstr_fd("boubou_shell: export: `", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd("': not a valid identifierf\n", 2);
        free(str);
        return (0);
    }
    rule = ft_returnrule(envnc, str);
    //printf("RULE = %s, a=%d,b=%d, %s\n", rule, ft_iseqin(str), ft_iseqin(rule), str);
    if (!ft_iseqin(cmd) && ft_iseqin(rule))
    {
     //   printf("tfriiit\n");
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

int ft_findsubinside(char *tofind, char *string)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!tofind || !string)
        return (0);
    while (string[i])
    {
        if (string[i] == tofind[j])
        {
            while (string[i] == tofind[j])
            {
                i++;
                j++;
            }
            if (!tofind[j])
                return (1);
            else
                j = 0;
        }
        i++;
    }
    return (0);
}

int ft_checkifplusinidentifier(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        if (str[i] == '+')
        {
            i++;
            if (str[i] == '=')
                return (0);
            else
                return (1);
        }
        i++;
    }
    return (0);
}

int ft_checkif_plusequal_existsinstring(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    if (ft_findsubinside("+=", str))
        return (1);
    if (str[0] = '+' || ft_checkifplusinidentifier(str) )
    {
        printf("%d\n", ft_checkifplusinidentifier(str));
        return (-1);
    }
    return (0);
}

void ft_printerror(char *str)
{
    ft_putstr_fd("boubou_shell: export: `", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);
}

char *ft_get_aftertheequalsign(char *str)
{
    int i;
    int j;
    char *ret;

    i = 0;
    j = 0;
    if (!str)
        return (NULL);
    while (str[i] && str[i] != '=')
        i++;
    i++;
    ret = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
    while (str[i])
    {
        ret[j] = str[i];
        i++;
        j++;
    }
    ret[j] = '\0';
    return (ret);
}

char *ft_returnjoinedrule(char *identifier, char *value, char *add)
{
    char *ret;
    char *tmp;

    tmp = ft_strjoin(identifier, "=");
    ret = ft_strjoin(tmp, value);
    free(tmp);
    tmp = ft_strjoin(ret, add);    free(str);
    x = envnoeq;
    while (x)
    {
        if (!ft_strcmp(x->str, iden))
            return (ft_strdup(x->str));
        x = x->next;
    }
    head = (*envnocmd);
    if (!cmnd->cmd[i])    
        printenv(head, fd);
    else
    {
        while (cmnd->cmd[i])
        {
            error = ft_checkif_plusequal_existsinstring(cmnd->cmd[i]);
            printf("%d\n", error);
                if (error == 1)
                {
                    iden = ft_retiden(cmnd->cmd[i]);
                    if (ft_checkifruleexists(*env, *envnocmd, cmnd->cmd[i]))
                    {    
                        rem = ft_returnjoinedrule(ft_retiden(cmnd->cmd[i]), fetchValue(iden,(*env)), ft_get_aftertheequalsign(cmnd->cmd[i]));
                        ft_unsetiden(env, envnocmd, iden);
                    }
                    add_before_last_node(envnocmd,rem);
                    free(iden);
                }
                else if (ft_checkrule(env, envnocmd, cmnd->cmd[i]) && error == 0)
                {
                    iden = ft_retidenplus(cmnd->cmd[i]);
                    if (ft_checkifruleexists(*env, *envnocmd, cmnd->cmd[i]))
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



