#include "../minishell.h"

int ft_count(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void ft_freenode(t_env *node)
{
    free(node->str);
    free(node);
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
            ft_freenode(current);
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
    char *str;
    int i;

    str = NULL;
    x = (*data)->env;
    i = 1;
    while (x)
    {
        if (ft_rulefinder(x->str, ft_strdup(rule)))
        {
            str = ft_strdup(x->str);
            deleteNodeByContent(&(*data)->env, x->str);
            deleteNodeByContent(&(*data)->envnoeq, str);
            break ;
        }
        y = x;
        x = x->next;
        i++;
    }
    if (str)
        free(str);
    free(rule);
}

void ft_rulefinderanddelete(t_data **data, char *rule)
{
    t_env *x;
    t_env *y;
    int i;

    x = (*data)->envnoeq;
    i = 1;
    while (x)
    {
        if (!ft_strcmp(x->str, rule))
        {
            deleteNodeByContent(&(*data)->envnoeq, x->str);
            break ;
        }
        y = x;
        x = x->next;
    }
    free(rule);
}

void    ft_unset(t_data **data, t_commands *cmnd)
{
    t_env *x;
    t_env *y;
    int i;
    int count;

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
        //printf("count = %d\n", count);
        ft_rulefinderanddelete(data, ft_strdup(cmnd->cmd[i]));
        i++;
    }
    g_exit_status = 0;
}
