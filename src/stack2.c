#include "stack.h"
#include <stdlib.h>
#include <unistd.h>

t_node	*st_get_node(t_stack *st, int n)
{
	int		i;
	t_node	*aux;

	i = 0;
	aux = st->top;
	while (aux && i < n)
	{
		aux = aux->next;
		i++;
	}
	return (aux);
}

void	*st_free_full(t_stack *st)
{
	t_node	*n;

	if (!st)
		return (0);
	while (st->top)
	{
		n = st_pop(st);
		if (n->aux)
			free (n->aux);
		free (n);
	}
	free (st);
	return (0);
}

void	*st_free(t_stack *st)
{
	t_node	*n;

	if (!st)
		return (0);
	while (st->top)
	{
		n = st_pop(st);
		free (n);
	}
	free (st);
	return (0);
}

int	st_reverse(t_stack **st)
{
	t_stack	*ret;
	t_node	*aux;
	t_node	*control;
	int		i;

	ret = st_new();
	i = 0;
	while (42)
	{
		i++;
		aux = st_pop(*st);
		if (!aux)
			break ;
		control = st_push(ret, aux->value);
		ret->top->aux = aux->aux;
		free (aux);
		if (!control)
			return ((int)st_free(ret));
	}
	free (*st);
	*st = ret;
	return (1);
}

int	st_empty(t_stack *st)
{
	if (st->top)
		return (0);
	return (1);
}
