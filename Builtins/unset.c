#include "../minishell.h"
a
void    ft_unset(t_data **data, t_commands *cmnd)
{
    t_env *x;
    t_commands *y;

    x = (*data)->env;
    y = cmnd;
    while (x)
    {
        while ()
            if (ft_rulefinder(x->str,cmnd->cmd))
    }
}
