#include "../minishell.h"

void    ft_env(t_env *env, int fd)
{
    t_env *cur;

    cur = env;
    while (cur)
    {    
        ft_putstr_fd(cur->str,fd);
        ft_putchar_fd('\n',fd);
        cur = cur->next;
    }  
}