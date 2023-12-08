#include <stdio.h>
#include <stdlib.h>

/**
 * struct dlistint_s - Doubly linked list node structure
 *
 * @n: Integer stored in the node
 * @prev: Pointer to the previous element of the list
 * @next: Pointer to the next element of the list
 */
typedef struct dlistint_s
{
    int n;
    struct dlistint_s *prev;
    struct dlistint_s *next;
} dlistint_t;

/**
 * get_dnodeint_at_index - Returns the nth node of a dlistint_t list
 * @head: Pointer to the head of the list
 * @index: Index of the node to retrieve
 *
 * Return: Pointer to the nth node, or NULL if it does not exist
 */
dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index)
{
    while (head != NULL && index > 0)
    {
        head = head->next;
        index--;
    }

    return head;
}

/**
 * delete_dnodeint_at_index - Deletes the node at the given index.
 * @head: Pointer to a pointer to the head of the list
 * @index: Index of the node to delete
 *
 * Return: 1 if successful, -1 if failed
 */
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
    dlistint_t *current, *temp;

    if (*head == NULL)
        return -1;

    current = get_dnodeint_at_index(*head, index);

    if (current == NULL)
        return -1;

    if (current == *head)
        *head = current->next;

    if (current->prev != NULL)
        current->prev->next = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;

    temp = current->next;
    free(current);

    return 1;
}
