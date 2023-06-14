
#include <common.h>

struct node *head = NULL;

void create_list(struct node **head)
{
	append(head, 10);
	append(head, 20);
	append(head, 30);
	append(head, 40);
	append(head, 50);

	return;
}

void free_list(struct node *head)
{
	struct node *tmp;
	struct node *ptr = head;

	while(ptr != NULL) {
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}

	return;
}

void print_list(struct node *head)
{
	struct node *ptr = head;

	while(ptr != NULL) {
		printf ("%d ", ptr->data);
		ptr = ptr->next;
	}

	printf ("\n");

	return;
}

int main()
{
	append_list_main();
	prepend_list_main();
	insert_at_main();
	reverse_list_main();

	return 0;
}
