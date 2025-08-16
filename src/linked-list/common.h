
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>

struct node {
	struct node *next;
	int data;
};

void create_list(struct node **head);
void free_list(struct node *head);
void print_list(struct node *head);
void append(struct node **head, int data);

void insert_at_main(void);
void append_list_main(void);
void prepend_list_main(void);
void reverse_list_main(void);

#endif
