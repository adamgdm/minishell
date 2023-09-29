#include "../minishell.h"

t_token*    _create_token(char *value, enum e_token type, enum e_state state, int space_check)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->content = value;
    token->type = type;
    token->state = state;
    token->space_check = space_check;
    token->before_expanded = ft_strdup("");
    token->next = NULL;
    return (token);
}

void    _add_token(t_token **head, t_token *new)
{
    t_token *current;

    if (!*head)
    {
        *head = new;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new;
}

void    _free_all_tokens(t_token **head)
{
    t_token *current;
    t_token *tmp;

    current = *head;
    int i = 1;
    while (current)
    {
        tmp = current;
        current = current->next;
        //free(tmp->content);
        free(tmp->before_expanded);
        free(tmp);
        i++;
    }
    *head = NULL;
}




