#include "stack.h"
#include <stdlib.h>

int	st_contains(t_stack *st, int n)
{
	t_node	*aux;
	int		ret;

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

t_node	*st_find(t_stack *st, int n)
{
	t_node	*aux;

	aux = st->top;
	while (aux)
	{
		if (aux->value == n)
			break ;
		aux = aux->next;
	}
	return (aux);
}

void	st_delete_node(t_stack *st, t_node *n)
{
	if (n)
		st_delete_pos(st, st_contains(st, n->value));
}

void	st_delete_pos(t_stack *st, int pos)
{
	int		i;
	t_node	*aux;
	t_node	*prev;

	aux = st->top;
	i = 0;
	if (pos < 0)
		return ;
	if (i == pos)
	{
		aux = st->top->next;
		free (st->top);
		st->top = aux;
		st->size--;
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
	st->size--;
}

int	st_pop_value(t_stack *st, int *n)
{
	t_node	*no;

	no = st_pop(st);
	if (!no)
		return (0);
	if (n)
		*n = no->value;
	free (no);
	return (1);
}
