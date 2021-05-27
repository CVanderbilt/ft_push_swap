#include "extras.h"

int	ft_bgoto_greater(t_data *d, int pivot, int has_first)
{
	t_node	*aux;
	int		index;
	int		first;
	int		last;

	aux = d->b->top;
	index = -1;
	while (aux && (++index || 1))
	{
		if (aux->value > pivot)
		{
			if (!has_first)
				first = index + has_first++;
			last = index;
		}
		aux = aux->next;
	}
	if (has_first && first <= d->b->size - last)
		while (d->b->top->value <= pivot)
			ft_execute_d(d, RB);
	else if (has_first)
		while (d->b->top->value <= pivot)
			ft_execute_d(d, RRB);
	return (has_first);
}

int	ft_simple_bsort3(t_data *d)
{
	t_node	*first;
	t_node	*second;
	t_node	*third;
	int		ret;

	ret = 1;
	first = d->b->top;
	second = first->next;
	third = second->next;
	if (third->value > first->value && first->value > second->value)
		ret = (ft_execute_d(d, RRB));
	else if (third->value > second->value && second->value > first->value)
		ret = ft_execute_d(d, SB) * ft_execute_d(d, RRB);
	else if (first->value > third->value && third->value > second->value)
		ret = ft_execute_d(d, SB) * ft_execute_d(d, RB);
	else if (second->value > third->value && third->value > first->value)
		ret = ft_execute_d(d, RB);
	else if (second->value > first->value && first->value > third->value)
		ret = (ft_execute_d(d, SB));
	ret *= ft_execute_d(d, PA) * ft_execute_d(d, PA) * ft_execute_d(d, PA);
	set_fs(d, d->a->top->value);
	ret *= ft_execute_d(d, RA) * ft_execute_d(d, RA) * ft_execute_d(d, RA);
	d->sorted += 3;
	return (ret);
}

int	ft_simple_bsort2(t_data *d)
{
	t_node	*first;
	t_node	*second;
	int		ret;

	first = d->b->top;
	second = first->next;
	if (first->value < second->value)
		if (!ft_execute_d(d, SB))
			return (0);
	ret = (ft_execute_d(d, PA) * ft_execute_d(d, PA));
	if (!d->sorted)
		d->first_sorted = d->a->top->value;
	ret *= ft_execute_d(d, RA) * ft_execute_d(d, RA);
	d->sorted += 2;
	return (ret);
}

int	ft_simple_bsort(t_data *d)
{
	int	ret;

	if (d->b->size == 3)
		return (ft_simple_bsort3(d));
	else if (d->b->size == 2)
		return (ft_simple_bsort2(d));
	else
	{
		ret = (ft_execute_d(d, PA));
		if (!d->sorted)
			d->first_sorted = d->a->top->value;
		ret *= ft_execute_d(d, RA);
		d->sorted++;
	}
	return (ret);
}

int	ft_bsort(t_data *d)
{
	int		aux;
	int		pivot;
	int		s;
	t_node	*n;

	n = d->b->top;
	s = d->b->size;
	aux = 0;
	if (s <= 3)
		return (ft_simple_bsort(d));
	pivot = ft_get_median(d->b);
	if (ft_num_is_min_or_max(d->b, pivot))
	{
		pivot = ((t_node *)n->next)->value;
		if (ft_num_is_min_or_max(d->b, pivot))
			pivot = ((t_node *)(((t_node *)n->next)->next))->value;
	}
	while (ft_bgoto_greater(d, pivot, 0))
	{
		ft_execute_d(d, PA);
	}
	if (!st_push(d->mem, d->a->top->value))
		return (0);
	return (1);
}
