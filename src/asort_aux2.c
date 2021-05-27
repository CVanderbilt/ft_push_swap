#include "asort_aux.h"

void	ft_fix_stoping(t_data *d, int *stop_at, int aux)
{
	t_node	*node;

	node = st_get_node(d->a, aux);
	if (d->sorted)
		*stop_at = d->first_sorted;
	else
	{
		*stop_at = st_get_node(d->a, aux - 1)->value;
		d->stoping = 0;
	}
	if (node)
		*stop_at = node->value;
}

int	ft_reposition(t_data *d, int count)
{
	t_inst	last;
	int		aux;

	last = RA;
	if (count < d->a->size - count)
		last = RRA;
	else
		count = d->a->size - count;
	aux = 0;
	while (aux < count && !d->first_loop)
	{
		ft_execute_d(d, last);
		aux++;
	}
	if (d->a->size - d->sorted > 0)
		if (!st_push(d->mem, d->a->top->value))
			return (0);
	return (1);
}

int	ft_sort_pivot(t_data *d, int pivot, int stop_at)
{
	int	count;

	count = 0;
	while (1)
	{
		if (!ft_agoto_lessereq(d, pivot, &count, stop_at))
			break ;
		ft_execute_d(d, PB);
	}
	return (ft_reposition(d, count));
}
