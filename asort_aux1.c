#include "asort_aux.h"

int	atop_sorted(t_data *d)
{
	int	min;

	min = -INT_MAX - 1;
	if (d->sorted)
		min = st_get_node(d->a, d->a->size - 1)->value + 1;
	if (!ft_get_min(d->a, min, &min))
		return (0);
	if (d->a->top->value == min)
		return (1);
	else if (((t_node *)d->a->top->next)->value == min)
	{
		ft_execute_d(d, SA);
		return (1);
	}
	return (0);
}

int	ft_auto_sort(t_data *d)
{
	int	aux;

	while (atop_sorted(d))
	{
		d->first_loop = 0;
		d->sorted++;
		if (d->mem->top && d->mem->top->value == d->a->top->value)
			st_pop_value(d->mem, &aux);
		ft_execute_d(d, RA);
		if (d->sorted >= d->a->size)
			return (1);
	}
	return (0);
}

int	ft_get_stoping_pos(t_data *d, int *stoping, int *stop_at)
{
	int	aux;

	while (42)
	{
		*stoping = 0;
		if (st_empty(d->mem))
			aux = d->a->size - d->sorted;
		else
		{
			st_pop_value(d->mem, stop_at);
			aux = st_contains(d->a, *stop_at);
			if (aux > 0)
				*stoping = 1;
		}
		if (aux < 0)
			return (1);
		if (aux > 0)
			break ;
	}
	return (aux);
}

int	ft_agoto_lessereq(t_data *d, int pivot, int *count, int stop_at)
{
	t_node	*n;
	int		pos;

	pos = 0;
	n = d->a->top;
	while (1)
	{
		if (!n || (d->stoping && n->value == stop_at))
			return (0);
		if (n->value <= pivot)
			break ;
		pos++;
		n = n->next;
	}
	while (pos > 0)
	{
		if (d->a->top->value <= pivot)
			break ;
		ft_execute_d(d, RA);
		*count = *count + 1;
		pos--;
	}
	return (1);
}
