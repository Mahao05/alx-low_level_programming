#include <stdio.h>
#include <stdlib.h>

/* Structure for doubly linked list nodes */
typedef struct dlistint_s {
    int data;
    struct dlistint_s *prev;
    struct dlistint_s *next;
} dlistint_t;

/**
 * free_dlistint - Frees a doubly linked list.
 * @head: Pointer to the head of the list.
 */
void free_dlistint(dlistint_t *head)
{
    dlistint_t *temp;


    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
