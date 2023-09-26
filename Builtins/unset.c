#include "../minishell.h"

void    ft_unset(t_data **data, t_commands *cmnd)
{
    t_env *x;
    t_env *z;
    t_commands *y;
    int i;

    i = 1;
    x = (*data)->env;
    z = (*data)->envnoeq;
    y = cmnd;
    if (!cmnd->cmd[i])
        return ;
    while (x && cmnd->cmd[i])
    {
        if (ft_rulefinder(x->str, ft_strjoin(cmnd->cmd[i], "=")))
        {
            deleteNode(&(*data)->env, x->str);
            x = (*data)->env;
            i++;
        }
        else
            x = x->next;
    }
    i = 1;
    while (z && cmnd->cmd[i])
    {
        if (ft_rulefinder(z->str, ft_strjoin(cmnd->cmd[i], "=")))
        {
            deleteNode(&(*data)->envnoeq, z->str);
            z = (*data)->env;
            i++;
        }
        else
            z = z->next;
    }
    i = 1;
    z = (*data)->envnoeq;
    while (z)
    {
        if (ft_doesmatch(z->str, cmnd->cmd[i]))
        {
            deleteNode(&(*data)->envnoeq, z->str);
            z = (*data)->env;
            i++;
        }
        else
            z = z->next;
    }
}