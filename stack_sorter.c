#include "stack.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int		ft_get_max(t_stack *st, int max, int *ret)
{
	t_node *aux;
	int control;

	control = 1;
	aux = st->top;
	while (aux)
	{
		if (aux->value <= max)
		{
			if (control || aux->value > *ret)
			{
				control = 0;
				*ret = aux->value;
			}
		}
		aux = aux->next;
	}
	if (!control)
		return (1);
	return (0);
}

int		ft_get_min(t_stack *st, int min, int *ret)
{
	t_node *aux;
	int control;

	control = 1;
	aux = st->top;
	while (aux)
	{
		if (aux->value >= min)
		{
			if (control || aux->value < *ret)
			{
				control = 0;
				*ret = aux->value;
			}
		}
		aux = aux->next;
	}
	if (!control)
		return (1);
	return (0);
}

int		ft_get_target(t_stack *a, t_stack *b, int min, int *control)
{
	int m1;
	int m2;
	int c1;
	int c2;
	
	c1 = ft_get_min(a, min, &m1);
	c2 = ft_get_min(b, min, &m2);
	if (!c1 && !c2)
	{
		*control = 0;
		return (1);
	}
	*control = 2;
	if (!c1)
		return (m2);
	else if (!c2)
	{
		*control = 1;
		return (m1);
	}
	else if (m1 < m2)
		*control = 1;
	return (intmin(m1, m2));
}

int ft_node_sorted(t_stack *a, t_stack *b, int n)
{
	t_node *aux;
	int pre_small;
	int post_big;
	int small_missing;
	int auxn;

	small_missing = 1;
	aux = a->top;
	while (aux && aux->value > n)
	{
		if (small_missing || pre_small > aux->value)
			pre_small = aux->value;
		small_missing = 0;
		aux = aux->next;
	}
	if (ft_get_min(b, -INT_MAX - 1, &auxn))
		if (small_missing || auxn < pre_small)
		{
			small_missing = 0;
			pre_small = auxn;
		}
	if (!aux)
		return (1);
	post_big = aux->value;
	while (aux)
	{
		if (post_big > aux->value)
			return (0);
		post_big = aux->value;
		aux = aux->next;
	}
	if (small_missing || post_big < pre_small)
		return (1);
	return (0);
}

t_inst	st_evaluate(t_stack *a, t_stack *b)
{
	int target;
	int control;
	int pos;
	int min;

	min = -INT_MAX - 1;
	while (1)
	{
		target = ft_get_target(a, b, min, &control);
		if (!control)
			return (END);
		if (control == 2 || !ft_node_sorted(a, b, target))
			break ;
		min = target + 1;
	}
	if (control == 1)
	{
		pos = st_contains(a, target);
		if (pos == 0)
			return (RA);
		if (pos == 1)
			return (SA);
		return (PB);
	}
	else
	{
		pos = st_contains(b, target);
		if (pos == 0)
			return (PA);
		if (pos == 1)
			return (SB);
		if (pos >= (int)st_size(b) / 2)
			return (RRB);
		return (RB);
	}
}