#include "../minishell.h"

void delete_last_node(t_env **head) {
    if (*head == NULL) {
        // List is empty, nothing to delete
        return;
    }

    if ((*head)->next == NULL) {
        // Only one node in the list, delete it
        free(*head);
        *head = NULL;
        return;
    }

    t_env *current = *head;
    t_env *previous = NULL;

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    free(current);
    previous->next = NULL;
}

// Function to add a node at the end of the list
void add_last_node(t_env **head, const char *str) {
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (new_node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    new_node->str = strdup(str);
    new_node->next = NULL;

    if (*head == NULL) {
        // If the list is empty, make the new node the head
        *head = new_node;
        return;
    }

    t_env *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
}

// Function to add a node before the last node
void add_bln(t_env **head, const char *str) {
    if (*head == NULL) {
        // If the list is empty, add a new node as the head
        add_last_node(head, str);
        return;
    }

    if ((*head)->next == NULL) {
        // Only one node in the list, add a new node before it
        t_env *new_node = (t_env *)malloc(sizeof(t_env));
        if (new_node == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        new_node->str = strdup(str);
        new_node->next = *head;
        *head = new_node;
        return;
    }

    t_env *current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (new_node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    new_node->str = strdup(str);
    new_node->next = current->next;
    current->next = new_node;
}

int ft_locatedelete(t_env **env, char *arraytofind) 
{
    if (env == NULL || *env == NULL || arraytofind == NULL) {
        return -1; // Invalid input or an empty list
    }

    t_env *current = *env;
    t_env *prev = NULL;
    int index = 0;

    while (current != NULL) {
        if (ft_rulefinder(current->str, arraytofind)) {
            // Found a match, so remove the node from the list
            if (prev == NULL) {
                // This is the first node
                *env = current->next;
            } else {
                prev->next = current->next;
            }

            // Free the memory of the node and its string
            free(current->str);
            free(current);

            return index; // Return the index of the deleted node
        }

        // Move to the next node
        prev = current;
        current = current->next;
        index++;
    }

    // If the node was not found, return -1
    return -1;
}