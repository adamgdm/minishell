#include "../minishell.h"

void free_env_list(t_env *head) {
    t_env *current = head;
    while (current != NULL) {
        t_env *temp = current;
        current = current->next;
        free(temp->str); // Free the string within the t_env struct
        free(temp);      // Free the t_env struct itself
    }
}

// Function to free a t_data struct, including its nested t_env structs
void free_t_data(t_data *data) {
    if (data != NULL) {
        free_env_list(data->env);      // Free the env linked list
        free_env_list(data->envnoeq);  // Free the envnoeq linked list
        free(data);                    // Free the t_data struct itself
    }
}

void    ft_exit(t_data *data)
{
    free_t_data(data);
    ft_putstr_fd("exit\n", 1);
    exit(0);
}