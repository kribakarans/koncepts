
/*

 Reverse a linked list by Iterative Method:

*/

#include <common.h>

void reverse_list(struct node **head)
{
	struct node *next = NULL;
	struct node *prev = NULL;
	struct node *curr = *head;

	while(curr != NULL) {
		/* Store next pointer */
		next = curr->next;

		/* Reverse current node's pointer */
		curr->next = prev;

		/* Move the pointers to next node */
		prev = curr;
		curr = next;
	}

	/* Point last node as head */
	*head = prev;

	return;
}

void reverse_list_main(void)
{
	struct node *head = NULL;

	create_list(&head);

	reverse_list(&head);

	print_list(head);

	free_list(head);

	return;
}

/* EOF */
