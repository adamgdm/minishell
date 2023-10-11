#include "../minishell.h"

void _do_norm(t_token *current, t_vars3 *vars)
{
    _parser_norm(current, &vars->out_file, &vars->error, &vars->already_printed);
    _parser_free_norm(current);
}