#include "../minishell.h"

int _norminette4(char *input, t_vars2 *vars)
{
    if (input[vars->i] == '\"' && !_norminette1(input, &vars->head, &vars->i, &vars->j))
        return (0);
    else if (input[vars->i] == '\'')
    {
        if (!_norminette2(input, &vars->head, &vars->i, &vars->j))
            return (0);
    }
    else
        _norminette3(input, &vars->head, &vars->s, &vars->i);
    return (1);
}