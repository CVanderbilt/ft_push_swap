#include "stack.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

t_stack *st_new()
{
	t_stack *ret;

	ret = (t_stack*)malloc(sizeof(t_stack));
	if (ret)
	{
		ret->top = 0;
		ret->size = 0;
	}
	return (ret);
}

unsigned int st_size(t_stack *st)
{
	int size;
	t_node *aux;

	size = 0;
	if (!st->top)
		return (size);
	aux = st->top;
	while (aux)
	{
		size++;
		aux = aux->next;
	}
	return (size);
}

t_node		*st_pop(t_stack *st)
{
	t_node *ret;

	if (!st->top)
		return (0);
	ret = st->top;
	st_delete_top(st);
	return (ret);
}

t_node 		*st_push(t_stack *st, int n)
{
	t_node *aux;

	aux = (t_node*)malloc(sizeof(t_node));
	if (!aux)
		return 0;
	aux->value = n;
	aux->next = st->top;
	//printf("hemos pusheado %p, apuntando a top %p\n", aux, st->top);
	st->top = aux;
	st->size++;
	return (aux);
}

void		st_delete_top(t_stack *st)
{
	if (st->top)
	{
		st->top = st->top->next;
		st->size--;
	}
}