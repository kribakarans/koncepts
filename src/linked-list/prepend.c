
/*

 Prepend list:
 Insert node at begining of the linked list. (stack model)

*/

#include <common.h>

void prepend(struct node **head, int data)
{
	struct node *new = NULL;

	/* 1. Create a new node */
	new = (struct node*)malloc(sizeof(*new));

	/* 2. Set data and next pointer of the new node */
	new->data = data;
	new->next = *head;

	/* 3. Update the head pointer to point to the new node */
	*head = new;

	return;
}

void prepend_list_main(void)
{
	struct node *head = NULL;

	prepend(&head, 10);
	prepend(&head, 20);
	prepend(&head, 30);
	prepend(&head, 40);
	prepend(&head, 50);

	print_list(head);

	free_list(head);

	return;
}

/* EOF */
