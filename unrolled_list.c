#include <malloc.h>
#include <assert.h>
#include <stdio.h>

#include "unrolled_list.h"

void list_init(struct UnrolledList *head)
{
	head->root = malloc(sizeof(struct Node));
	head->root->count = 0;
	head->root->next = head->root;
	head->root->prev = head->root;
}

// append to end
static void list_create_node(struct UnrolledList *head)
{
	struct Node *new_node = malloc(sizeof(struct Node));
	new_node->count = 0;
	new_node->prev = head->root->prev;
	new_node->next = head->root;
	head->root->prev->next = new_node;
	head->root->prev = new_node;
}

void list_push(struct UnrolledList *head, double value)
{
	struct Node *iterator = head->root->prev;
	do
	{
		if (iterator->count == ARRAY_SIZE)
		{
			// add new node
			list_create_node(head);
			// next
			iterator = iterator->next;
		}
		else
		{
			iterator->array[iterator->count++] = value;
			return;
		}
	}
	while (iterator != head->root);
}

// delete last node
static void list_delete_node(struct UnrolledList *head)
{
	if (head->root->prev == head->root)
	{
		head->root->count = 0;
		return;
	}
	struct Node *to_delete = head->root->prev;
	head->root->prev->prev->next = head->root;
	head->root->prev = head->root->prev->prev;
	free(to_delete);
}

double list_pop(struct UnrolledList *head)
{
	struct Node *iterator = head->root->prev;
	do
	{
		// delete empty node
		if (iterator->count == 0)
		{
			// shift to left
			iterator = iterator->prev;
			// and delete
			list_delete_node(head);
			continue;
		}
		else
			return iterator->array[--iterator->count];
	}
	while (iterator != head->root);
	fprintf(stderr, "Can't remove element from empty list\n");
	return -1.0;
}

int list_get_size(struct UnrolledList *head)
{
	int size = 0;
	struct Node *iterator = head->root;
	do
	{
		size += iterator->count;
		iterator = iterator->next;
	}
	while (iterator != head->root);
	return size;
}

void list_get_array(struct UnrolledList *head, double *another_array, int size)
{
	// int list_size = list_get_size(head);
	struct Node *iterator = head->root;
	int offset = 0;
	do
	{
		for (int i = 0; i < ARRAY_SIZE && i < size; ++i)
			another_array[i + offset] = iterator->array[i];
		offset += ARRAY_SIZE;
		size -= ARRAY_SIZE;
		iterator = iterator->next;
	}
	while (iterator != head->root && size != 0);
}

double *list_get_ref_by(struct UnrolledList *head, int index)
{
	int list_size = list_get_size(head);
	if (index >= list_size || index < 0)
	{
		fprintf(stderr, "Incorrect index %d. List size - %d\n", index, list_size);
		return NULL;
	}

	struct Node *iterator = head->root;
	while (index >= ARRAY_SIZE)
	{
		iterator = iterator->next;
		index -= ARRAY_SIZE;
	}
	return &iterator->array[index];
}

double list_get_by(struct UnrolledList *head, int index)
{
	double *return_value = list_get_ref_by(head, index);
	if (return_value == NULL)
		return -1.0;
	return *return_value;
}

static double find_max(double *array, int size)
{
	if (size == 0)
	{
		fprintf(stderr, "0 size array\n");
		return -1.0;
	}
	double max = array[0];
	for (int i = 1; i < size; ++i)
		if (array[i] > max) max = array[i];
	return max;
}

double list_max(struct UnrolledList *head)
{
	struct Node *iterator = head->root;
	double global_max = find_max(iterator->array, iterator->count);
	do
	{
		double local_max = find_max(iterator->array, iterator->count);
		if (local_max > global_max) global_max = local_max;
		iterator = iterator->next;
	}
	while (iterator != head->root);
	return global_max;
}

void list_clean(struct UnrolledList *head)
{
	struct Node *iterator = head->root->prev;
	while (iterator != head->root)
	{
		struct Node *to_delete = iterator;
		iterator = iterator->prev;
		free(to_delete);
	}
	
	head->root->next = head->root;
	head->root->prev = head->root;
	head->root->count = 0;
}

void list_terminate(struct UnrolledList *head)
{
	list_clean(head);
	free(head->root);
	head->root = NULL;
}

void list_print(struct UnrolledList *head)
{
	struct Node *iterator = head->root;
	do
	{
		for (int i = 0; i < iterator->count; ++i)
			printf(" %7.4lf", iterator->array[i]);
		putchar('\n');
		iterator = iterator->next;
	}
	while (iterator != head->root);
}
