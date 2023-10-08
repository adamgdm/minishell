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

void    ft_env(t_data **data)
{
    t_env *cur;
    t_env *node;

    node = (*data)->env;
    cur = (*data)->env;
   // ft_exportpwdoldpwd(data, pwd);
    while (node)
    {
        if (ft_rulefinder(node->str, ft_strdup("_")))
            break ;
        if (!node->next)
            add_last_node(&(*data)->env, ft_strdup("_=env"));
        node = node->next;
    }
    while (cur)
    {    
        printf("%s\n", cur->str);
        cur = cur->next;
    }
    g_exit_status = 0;
}