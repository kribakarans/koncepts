
/*

 Insert node at nth position end of the linked list.

*/

#include <common.h>

void insert_at_node(struct node **head, int data, int pos)
{
	struct node *ptr = NULL;
	struct node *new = NULL;

	/* Create new node */
	new = (struct node*)malloc(sizeof(*new));

	/* Set data and next pointer of the new node */
	new->data = data;

	/* If the linked list is empty or the position is 0, insert at the beginning */
	if ((*head == NULL) || (pos == 0)) {
		new->next = *head; /* mostly it holds NULL */
		*head = new;
		return;
	}

	/* Traverse to the nth position */
	ptr = *head;
	for (int i = 1; i < pos; i++) {
		if (ptr == NULL) {
			printf("Oops! position is out of range\n");
			free(new);
			return;
		}

		ptr = ptr->next;
	}

	/* Insert the new node after the nth position */
	new->next = ptr->next;
	ptr->next = new;

	return;
}

void insert_at_main(void)
{
	struct node *head = NULL;

	create_list(&head);

	insert_at_node(&head, 15, 1);
	insert_at_node(&head, 25, 3);

	print_list(head);

	free_list(head);

	return;
}

/* EOF */
