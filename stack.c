#include "stack.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//lo podemos omitir y usar t_stack sin puntero
t_stack *st_new()
{
	t_stack *ret;

	ret = (t_stack*)malloc(sizeof(t_stack));
	if (ret)
		ret->top = 0;
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
	return (aux);
}

void		st_delete_top(t_stack *st)
{
	if (st->top)
	{
		st->top = st->top->next;
	}
}

int 		st_contains(t_stack *st, int n)
{
	t_node *aux;
	int ret;

	ret = 0;
	aux = st->top;
	while (aux)
	{
		if (aux->value == n)
			return (ret);
		else
			aux = aux->next;
		ret++;
	}
	return (-1);
}

t_node 		*st_find(t_stack *st, int n)
{
	t_node *aux;

	aux = st->top;
	while (aux)
	{
		if (aux->value == n)
			break ;
		aux = aux->next;
	}
	return (aux);
}

void 		st_delete_pos(t_stack *st, int pos)
{
	int i;
	t_node *aux;
	t_node *prev;

	aux = st->top;
	i = 0;
	if (pos < 0)
		return ;
	if (i == pos)
	{
		aux = st->top->next;
		free (st->top);
		st->top = aux;
	}
	while (i < pos && aux)
	{
		prev = aux;
		aux = aux->next;
	}
	if (!aux)
		return ;
	prev->next = aux->next;
	free (aux);
}

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
			return (0);
		aux = aux->next;
	}
	st_reverse(&ret);
	return (ret);
}

int st_free(t_stack *st)
{
	while(st->top)
		free(st_pop(st));
	free (st);
	return (0);
}