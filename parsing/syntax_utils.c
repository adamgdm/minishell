#include "../minishell.h"

int _syntax_norm(t_token *current)
{
    if (!current->next)
    {
        printf("minishell: syntax error near unexpected token `newline'\n");
        g_exit_status = 258;
        return (1);
    }
    if (_check_type(current->next->type) || current->next->type == PIPE)
    {
        printf("minishell: syntax error near unexpected token `%s'\n", current->next->content);
        g_exit_status = 258;
        return (1);
    }
    return (0);
}

int _syntax_norm2(t_token *current)
{
    if (!current->next || current->next->type == PIPE)
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        g_exit_status = 258;
        return (1);
    }
    return (0);
}

int _syntax_norm4(t_token *current)
{
    if (_check_type(current->type))
    {
        if (_syntax_norm(current))
            return (1);
    }
    if (current->type == PIPE)
    {
        if (_syntax_norm2(current))
            return (1);
    }
    return (0);
}


int _syntax_norm3(t_token *current)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = 0;
    while (current->content[i])
    {
        if (current->content[0] == '(')
            return (_syntax_norm7(current, i));
        if (current->content[0] == ')')
        {
            printf("minishell: syntax error near unexpected token `)'\n");
            g_exit_status = 258;
            return (1);
        }
        if (current->content[i] == '(')
        {
            printf("minishell: syntax error near unexpected token `('\n");
            g_exit_status = 258;
            return (1);
        }
        i++;
    }
    return (0);
}
