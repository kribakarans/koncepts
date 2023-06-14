
/*

 Append list:
 Insert node at end of the linked list.

*/

#include <common.h>

void append(struct node **head, int data)
{
	struct node *ptr = NULL;
	struct node *new = NULL;

	/* Create new node */
	new = (struct node*)malloc(sizeof(*new));

	/* Set data and next pointer of the new node */
	new->data = data;
	new->next = NULL;

	/* If the linked list is empty, make the new node the head */
	if (*head == NULL) {
		*head = new;
		return;
	}

	/* Traverse to the last node */
	ptr = *head;
	while(ptr->next != NULL) {
		ptr = ptr->next;
	}

	/* Insert the new node to the last node */
	ptr->next = new;

	return;
}

void append_list_main(void)
{
	struct node *head = NULL;

	append(&head, 10);
	append(&head, 20);
	append(&head, 30);
	append(&head, 40);
	append(&head, 50);

	print_list(head);

	free_list(head);

	return;
}

/* EOF */
