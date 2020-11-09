#ifndef ___UNROLLED_LIST_H___
#	define ___UNROLLED_LIST_H___

#	define ARRAY_SIZE 10

struct Node
{
	double array[ARRAY_SIZE];
	int count;
	struct Node *next;
	struct Node *prev;
};

struct UnrolledList
{
	struct Node *root;
};


extern void list_init(struct UnrolledList *head);
extern void list_push(struct UnrolledList *head, double value);
extern double list_pop(struct UnrolledList *head);
extern int list_get_size(struct UnrolledList *head);
extern void list_get_array(struct UnrolledList *head, double *another_array, int size);
extern double list_get_by(struct UnrolledList *head, int index);
extern double list_max(struct UnrolledList *head);
extern void list_clean(struct UnrolledList *head);
extern void list_terminate(struct UnrolledList *head);
extern void list_print(struct UnrolledList *head);

#endif // ___UNROLLED_LIST_H___