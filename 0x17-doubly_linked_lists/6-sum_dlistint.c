#include <stdio.h>

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
 * sum_dlistint - Returns the sum of all the data (n) of a dlistint_t list
 * @head: Pointer to the head of the list
 *
 * Return: The sum of all the data (n) of the list, or 0 if the list is empty
 */
int sum_dlistint(dlistint_t *head)
{
    int sum = 0;


    while (head != NULL)
    {
        sum += head->n;
        head = head->next;
    }


    return sum;
}
