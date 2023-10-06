#include "../minishell.h"

int ft_strcmpwithoutnull(char *str, char *rts)
{
    int i;

    i = 0;
    if (!str || !rts)
        return (1);
    while (str[i] && rts[i])
    {
        if (str[i] != rts[i])
            return (1);
        i++;
    }
    if (str[i] != rts[i])
        return (1);
    return (0);
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
    free(cmnd);
    free(data);
}

char **ft_parse_args(char *str)
{
    char **returnval;
    int condition;
    int i;

    i = 0;
    returnval = malloc(sizeof(char *) * 4);
    while(str[i])
    {
        condition = 0;
        if (str[i] == '=')
        {
            if (i != 0)
            {
                if (str[i - 1] == '+')
                {
                    returnval[0] = ft_substr(str, 0, i - 1);
                    condition = 1;
                }
                else
                    returnval[0] = ft_substr(str, 0, i);
            }
            else
                returnval[0] = ft_substr(str, 0, i);
            if (str[i + 1] == '\0')
                returnval[1] = ft_strdup("");
            else
                returnval[1] = ft_substr(str, i + 1, ft_strlen(str));
            if (condition == 1)
                returnval[2] = ft_strdup("+=");
            else
                returnval[2] = ft_strdup("=");
            returnval[3] = 0;
            return (returnval);
        }
        i++;
    }
    returnval[0] = ft_strdup(str);
    returnval[1] = 0;
    returnval[2] = 0;
    returnval[3] = 0;
    return (returnval);
}

char *ft_returnrule(t_env *env, char *rts)
{
    t_env *x;
    char *str;

    x = env;
    while (x)
    {
        str = ft_strjoin(rts, "=");
        if (ft_rulefinder(x->str, str))
            return (ft_strdup(x->str));
        x = x->next;
    }
    return (0);
}

int ft_ruleexist(t_data **data, char *iden)
{
    t_env *x;
    char *str;
    char *rule;

    x = (*data)->env;
    str = ft_strjoin(iden, "=");
    while (x)
    {
        rule = ft_strdup(str);
        if (ft_rulefinder(x->str, rule))
        {
            free(str);
            return (1);
        }
        x = x->next;
    }
    x = (*data)->envnoeq;
    while (x)
    {
        if (!ft_strcmp(x->str, iden))
        {
            free(str);
            return (1);
        }
        x = x->next;
    }
    free(str);
    return (0);
}

int ft_checkexportorappend(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (2);
    if (str[0] == '+')
        return (1);
    if (str[0] == '=')
        return (2);
    return (0);
}

void ft_exporttherule(t_data **data, char *iden, char *value)
{
    char *str = NULL;
    char *tmp = NULL;
    t_env *env;
    t_env *envnoeq;

    env = (*data)->env;
    envnoeq = (*data)->envnoeq;
    if (ft_ruleexist(data, iden) && !value)
    {
        return ;
    }
    else if (ft_ruleexist(data, iden) && value)
    {
        str = ft_strjoin(iden, "=");
        tmp = ft_strjoin(str, value);
        ft_unsetiden(&env, &envnoeq, iden);
        add_before_last_node(&(*data)->env, tmp);
        add_before_last_node(&(*data)->envnoeq, tmp);
    }
    else 
    {
        printf("hani hna\n");
        if (value)
        {
            str = ft_strjoin(iden, "=");
            tmp = ft_strjoin(str, value);
            add_before_last_node(&env, tmp);
        }
        else
            tmp = ft_strdup(iden);
        add_last_node(&envnoeq, tmp);
    }
    if (str)
        free (str);
    if (tmp)
        free (tmp);
}

char *ft_getvalue(char *str)
{
    int i;
    char *value;

    i = 0;
    if (!str)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '=')
            break ;
        i++;
    }
    if (!str[i])
        return (NULL);
    value = ft_substr(str, i + 1, ft_strlen(str));
    return (value);
}

void ft_append(t_data **data, char *iden, char *value)
{
    char *rts;
    char *str;
    char *tmp;
    if (!ft_ruleexist(data, iden))
    {
        printf("ident = %s\n", iden);
        ft_exporttherule(data, iden, value);
    }
    else
    {
        rts = ft_returnrule((*data)->envnoeq, iden);
        str = ft_getvalue(rts);
        if (str && value)
            tmp = ft_strjoin(str, value);
        else
            tmp = ft_strdup(value);
        ft_unsetiden(&((*data)->env), &((*data)->envnoeq), iden);
        ft_exporttherule(data, iden, tmp);
        free(tmp);
        free(rts);
        free(str);
    }
}

void ft_free_array(char **array)
{
    int i;

    i = 0;
    if (array[0])
        free (array[0]);
    if (array[1])
        free (array[1]);
    if (array[2])
        free (array[2]);
    free(array);
}

void ft_printenv(t_env *env, int fd)
{
    t_env *x;
    char **args;

    x = env;
    while (x)
    {
        args = ft_parse_args(x->str);
        ft_putstr_fd("declare -x ", fd);
        ft_putstr_fd(args[0], fd);
        if (args[1])
        {
            ft_putstr_fd("=\"", fd);
            ft_putstr_fd(args[1], fd);
            ft_putstr_fd("\"", fd);
        }
        ft_putstr_fd("\n", fd);
        ft_free_array(args);
        x = x->next;
    }
}

void printargs(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        // // // printf("args[%d] = %s\n", i, args[i]);
        i++;
    }
}

int ft_printerror(char *str)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);
    return (1);
}

int ft_checkerrors(char *command, char *identifier)
{
    char *str;
    int i;

    i = 0;
    // // // printf("identifier is %s\n", identifier);
    if (identifier[0] != '_' && !ft_isalpha(identifier[0]))
        return(ft_printerror(identifier));
    while (identifier[i])
    {
        if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
        {
            if (identifier[i] == '+')
                return(ft_printerror(command));
            else
                return(ft_printerror(identifier));
        }
        i++;
    }
    return (0);
}

void ft_export(t_data **data, char **args, int fd)
{
    char **arguments;
    int i;

    i = 1;
    if (!args[i])
    {
        ft_printenv(((*data)->envnoeq), fd);
        return ;
    }
    while (args[i])
    {
        arguments = ft_parse_args(args[i]);
        if (!ft_checkerrors(args[i], arguments[0]))
        {
            if (ft_checkexportorappend(arguments[2]) == 1)
                ft_append(data, arguments[0], arguments[1]);
            else if (ft_checkexportorappend(arguments[2]) == 2)
                ft_exporttherule(data, arguments[0], arguments[1]);
        }
        i++;
        ft_freearr(arguments);
    }
}