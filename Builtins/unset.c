#include "../minishell.h"

int ft_count(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void deleteNodeByContent(t_env **head, const char *target) {
    if (*head == NULL) {
        return; // List is empty, nothing to delete
    }

    t_env *current = *head;
    t_env *prev = NULL;

    // Traverse the list
    while (current != NULL) {
        // Compare the content of the current node with the target
        if (strcmp(current->str, target) == 0) {
            // Found a match, unlink and delete the node
            if (prev == NULL) {
                // If it's the head node, update the head pointer
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return; // Node deleted, exit the function
        }

        // Move to the next node
        prev = current;
        current = current->next;
    }
}

void ft_rulefinderanddelete_eq(t_data **data, char *rule)
{
    t_env *x;
    t_env *y;
    int i;

    x = (*data)->env;
    y = (*data)->envnoeq;
    i = 1;
    while (x)
    {
        if (ft_rulefinder(x->str, ft_strdup(rule)))
        {
            deleteNodeByContent(&(*data)->envnoeq, x->str);
        }
        y = x;
        x = x->next;
        i++;
    }
}

void ft_rulefinderanddelete(t_data **data, char *rule)
{
    t_env *x;
    t_env *y;
    int i;

    x = (*data)->env;
    y = (*data)->envnoeq;
    i = 1;
    while (x)
    {
        if (!ft_strcmp(x->str, rule) == 0)
        {
            if (i == 1)
            {
                (x) = (x)->next;
                free(x->str);
                free(x);
                return ;
            }
            else
            {
                y->next = x->next;
                free(x->str);
                free(x);
                return ;
            }
        }
        y = x;
        x = x->next;
        i++;
    }
}
/*
void    ft_unset(t_data **data, t_commands *cmnd)
{
    t_env *x;
    t_env *y;
    int i;
    int count;

    x = (*data)->env;
    y = (*data)->envnoeq;
    count = ft_count(cmnd->cmd);
    i = 1;
    while (i < count)
    {
        ft_rulefinderanddelete_eq(data, ft_strjoin(cmnd->cmd[i], "="));
        i++;
    }
    i = 1;
    while (i < count)
    {
        ft_rulefinderanddelete(data, ft_strdup(cmnd->cmd[i]));
        i++;
    }
}
*/
void    ft_unset(t_data **data, t_commands *cmnd)
{
    t_env *x;
    t_env *z;
    t_commands *y;
    int i;
    int j;

    i = 1;
    j = ft_count(cmnd->cmd);
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
    while (z && cmnd->cmd[i])
    {
        if (!ft_strcmp(z->str, cmnd->cmd[i]))
        {
            deleteNode(&(*data)->envnoeq, z->str);
            z = (*data)->env;
            i++;
        }
        else
            z = z->next;
    }
}