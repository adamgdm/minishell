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
void free_t_data(t_data **dat) 
{   
    t_data *data;

    data = *dat; 
    if (data != NULL) {
        free_env_list(data->env);      // Free the env linked list
        free_env_list(data->envnoeq);  // Free the envnoeq linked list
        free(data);                    // Free the t_data struct itself
    }
}

void free_commands(t_commands *head) {
    t_commands *current = head;
    while (current != NULL) {
        t_commands *temp = current;
        current = current->next;

        // Free the memory allocated for the cmd array
        if (temp->cmd != NULL) {
            for (int i = 0; temp->cmd[i] != NULL; i++) {
                free(temp->cmd[i]);
            }
            free(temp->cmd);
        }

        // Free the current node
        free(temp);
    }
}

void    ft_exit(t_data **data, t_commands *cmnds)
{
    free_commands(cmnds);
    free_t_data(data);
    ft_putstr_fd("exit\n", 1);
    exit(0);
}