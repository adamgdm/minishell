#include "../minishell.h"

void    _update_tokens(t_token** result)
{
    t_token *current;
    t_token *tmp;

    current = *result;
    while (current->next)
    {
        if (current->type == WORD && current->space_check == 0 && current->next->type == WORD)
        {
            current->content = ft_strjoin(current->content, current->next->content);
            current->before_expanded = _append(current->before_expanded, ' ');
            current->before_expanded = ft_strjoin(current->before_expanded, current->next->before_expanded);
            if (current->state + current->next->state != 0)
                current->state = QUOTED;
            
            tmp = current->next;
            if (current->next && current->next->space_check == 1)
                current->space_check = 1;
            current->next = current->next->next;
            free(tmp);
        }
        else
            current = current->next;
    }
}