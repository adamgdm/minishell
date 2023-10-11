#include "../minishell.h"

void    _update_tokens(t_token** result)
{
    t_token *current;
    t_token *tmp;
    char    *s;

    current = *result;
    while (current->next)
    {
        if (current->type == WORD && current->space_check == 0 && current->next->type == WORD)
            _update_tokens_utils(current);
        else
            current = current->next;
    }
}