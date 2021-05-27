#include "extras.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int	ft_get_max(t_stack *st, int max, int *ret)
{
	t_node	*aux;
	int		control;

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

int	ft_get_min(t_stack *st, int min, int *ret)
{
	t_node	*aux;
	int		control;

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

int	ft_node_last_check(t_node *aux, int small_missing, int pre_small)
{
	int	post_big;

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

int	ft_node_sorted(t_stack *a, t_stack *b, int n)
{
	t_node	*aux;
	int		pre_small;
	int		small_missing;
	int		auxn;

	small_missing = 1;
	aux = a->top;
	while (aux && aux->value > n)
	{
		if (small_missing || pre_small > aux->value)
			pre_small = aux->value;
		small_missing = 0;
		aux = aux->next;
	}
	if (ft_get_min(b, -INT_MAX - 1, &auxn)
		&& (small_missing || auxn < pre_small))
	{
		small_missing = 0;
		pre_small = auxn;
	}
	return (ft_node_last_check(aux, small_missing, pre_small));
}
