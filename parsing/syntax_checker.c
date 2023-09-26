#include "../minishell.h"


int _check_type(enum e_token type)
{
    if (type == REDIRECT_IN || type == REDIRECT_OUT || type == REDIRECT_APPEND || type == HERE_DOC) 
        return (1);
    return (0);
}


int _syntax_check(t_token** result)
{
    t_token*    current;

    current = *result;
    if (current->type == PIPE)
    {
        printf("syntax error near unexpected token `|'\n");
        return (1);
    }
    
    while (current)
    {
        if (_check_type(current->type))
        {
            if (!current->next)
            {
                printf("syntax error near unexpected token `newline'\n");
                return (1);
            }
            if (_check_type(current->next->type) || current->next->type == PIPE)
            {
                printf("syntax error near unexpected token `%s'\n", current->next->content);
                return (1);
            }
        }
        if (current->type == PIPE)
        {
            if (!current->next)
            {
                printf("syntax error near unexpected token `newline'\n");
                return (1);
            }
            if (current->next->type == PIPE)
            {
                printf("syntax error near unexpected token `|'\n");
                return (1);
            }
        }
        current = current->next;
    }
    return (0);

} 