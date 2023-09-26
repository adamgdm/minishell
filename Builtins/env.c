#include "../minishell.h"

void    ft_env(t_env **env, int fd)
{
    t_env *cur;
    t_env *node;
    char *pwd;

    // pwd = ft_retpwd;
    node = (*env);
    cur = (*env);
    while (node)
    {
        if (ft_rulefinder(node->str, ft_strdup("_=env")))
            break ;
        if (!node->next)
            add_last_node(env, ft_strdup("_=env"));
        node = node->next;
    }
    while (cur)
    {    
        ft_putstr_fd(cur->str,fd);
        ft_putchar_fd('\n',fd);
        cur = cur->next;
    }  
}