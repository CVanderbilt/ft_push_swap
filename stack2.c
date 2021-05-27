#include "stack.h"
#include <stdlib.h>
#include <unistd.h>

t_node		*st_get_node(t_stack *st, int n)
{
	int i;
	t_node *aux;

	i = 0;
	aux = st->top;
	while (aux && i < n)
	{
		aux = aux->next;
		i++;
	}
	return (aux);
}

t_stack *st_dup(t_stack *st)
{
	t_node *aux;
	t_stack *ret;

	ret = st_new();
	if (!ret)
		return (0);
	aux = st->top;
	while (aux)
	{
		if (!st_push(ret, aux->value)) //deja leaks
			return ((t_stack*)st_free(ret));
		aux = aux->next;
	}
	if (!st_reverse(&ret))
		return ((t_stack*)st_free(ret));
	return (ret);
}

void *st_free(t_stack *st)
{
	while(st->top)
		free(st_pop(st));
	free (st);
	return (0);
}

int 	st_reverse(t_stack **st)
{
	t_stack *ret;
	t_node *aux;
	t_node *control;

	ret = st_new();
	int i = 0;
	while (42)
	{
		i++;
		aux = st_pop(*st);
		if (!aux)
			break ;
		control = st_push(ret, aux->value);
		free (aux);
		if (!control)
			return (0);
	}
	free (*st);
	*st = ret;
	return (1);
}

int 	st_empty(t_stack *st)
{
	if (st->top)
		return (0);
	return (1);
}