#include "extras.h"
#include "asort_aux.h"

int	ft_simple_asort3(t_data *d)
{
	t_node	*first;
	t_node	*second;
	t_node	*third;
	int		ret;

	first = d->a->top;
	second = first->next;
	third = second->next;
	if (third->value > first->value && first->value > second->value)
		ret = ft_execute_d(d, SA) * set_fs(d, d->a->top->value)
			* ft_execute_d(d, RA) * ft_execute_d(d, RA) * ft_execute_d(d, RA);
	else if (second->value > first->value && first->value > third->value)
		ret = ft_execute_d(d, PB) * ft_execute_d(d, SA)
			* set_fs(d, d->a->top->value) * ft_execute_d(d, RA)
			* ft_execute_d(d, PA) * ft_execute_d(d, RA) * ft_execute_d(d, RA);
	else if (first->value > second->value && second->value > third->value)
		ret = ft_execute_d(d, PB) * ft_execute_d(d, SA)
			* set_fs(d, d->a->top->value) * ft_execute_d(d, RA)
			* ft_execute_d(d, RA) * ft_execute_d(d, PA) * ft_execute_d(d, RA);
	else
		ret = ft_execute_d(d, SA) * set_fs(d, d->a->top->value)
			* ft_execute_d(d, RA) * ft_execute_d(d, SA) * ft_execute_d(d, RA)
			* ft_execute_d(d, RA);
	d->sorted += 3;
	return (ret);
}

int	ft_simple_asort2(t_data *d)
{
	int	ret;

	ret = 1;
	if (d->a->top->value > ((t_node *)(d->a->top->next))->value)
		ret = ft_execute_d(d, SA);
	if (!d->sorted)
		d->first_sorted = d->a->top->value;
	d->sorted += 2;
	ret *= (ft_execute_d(d, RA) * ft_execute_d(d, RA));
	return (ret);
}

int	ft_simple_asort1(t_data *d)
{
	if (!d->sorted)
		d->first_sorted = d->a->top->value;
	d->sorted++;
	return (ft_execute_d(d, RA));
}

int	ft_simple_asort(t_data *d, int aux)
{
	if (aux == 3)
		return (ft_simple_asort3(d));
	if (aux == 2)
		return (ft_simple_asort2(d));
	return (ft_simple_asort1(d));
}

int	ft_asort(t_data *d)
{
	int		pivot;
	int		aux;
	int		aux2;
	int		stoping;
	int		stop_at;

	d->stoping = 1;
	aux2 = 0;
	if (ft_auto_sort(d))
		return (1);
	aux = ft_get_stoping_pos(d, &stoping, &stop_at);
	if (aux <= 3)
		return (ft_simple_asort(d, aux));
	ft_fix_stoping(d, &stop_at, aux);
	if (d->stoping)
		pivot = ft_get_median_section(d->a, 0, aux - 1);
	else
		pivot = ft_get_median_section(d->a, 0, aux);
	return (ft_sort_pivot(d, pivot, stop_at));
}
