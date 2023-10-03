#include "../minishell.h"

t_commands *ft_createcommand(char **str)
{
    t_commands *newnode;

    newnode = malloc(sizeof(t_commands));
    newnode->in_file = -1;
    newnode->cmd = str;
    newnode->next = NULL;
    newnode->out_file = 1;
    return (newnode);
}

void ft_freecmd(t_commands *cmd)
{
    int i;

    i = 0;
    while (cmd->cmd[i])
    {
        free(cmd->cmd[i]);
        i++;
    }
    free(cmd->cmd);
    free(cmd);
}

void ft_freearr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void ft_exportpwdoldpwd(t_data **data, char *pwd)
{
    char **cmd;
    char *str;
    t_commands *comond;
    char *newpwd;

    comond = ft_createcommand(ft_split("unset OLDPWD", ' '));
    ft_unset(data, comond);
    ft_freecmd(comond);
    str = ft_strjoin("export OLDPWD=", pwd);
    cmd = ft_split(str, ' ');
    ft_export(data, cmd, 1);
    free(str);
    comond = ft_createcommand(ft_split("unset PWD", ' '));
    ft_unset(data, comond);
    ft_freecmd(comond);
    ft_freearr(cmd);
    newpwd = ft_returnpwd();
    str = ft_strjoin("export PWD=", newpwd);
    cmd = ft_split(str, ' ');
    ft_export(data, cmd, 1);
    free(str);
    ft_freearr(cmd);
    free(newpwd);
}

void    ft_env(t_data **data, char *pwd, int fd)
{
    t_env *cur;
    t_env *node;

    node = (*data)->env;
    cur = (*data)->env;
    ft_exportpwdoldpwd(data, pwd);
    while (node)
    {
        if (ft_rulefinder(node->str, ft_strdup("_=env")))
            break ;
        if (!node->next)
            add_last_node(&(*data)->env, ft_strdup("_=env"));
        node = node->next;
    }
    while (cur)
    {    
        ft_putstr_fd(cur->str,fd);
        ft_putchar_fd('\n',fd);
        cur = cur->next;
    }  
}