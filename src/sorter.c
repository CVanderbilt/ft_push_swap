#include "extras.h"

t_inst	ft_try_double(t_stack *b, t_inst last)
{
	int	min;

	if (last == SA || last == RA)
	{
		ft_get_min(b, -INT_MAX, &min);
		min = st_contains(b, min);
		if (min == 1 && last == SA)
			return (SS);
		else if (last == RA && min >= (int)st_size(b) / 2)
			return (RR);
	}
	return (last);
}

int	ft_init_data(t_data *d, t_stack *a)
{
	d->first_loop = 1;
	d->a = a;
	d->sorted = 0;
	d->mem = st_new();
	if (!d->mem)
		return ((int)st_free(a));
	d->b = st_new();
	if (!d->b)
		return ((int)st_free(d->mem) + (int)st_free(d->a));
	d->ih = st_new();
	if (!d->ih)
		return ((int)st_free(d->mem) + (int)st_free(d->a) + (int)st_free(d->b));
	return (st_size(a));
}

int	ft_print_biggest(t_stack *a, t_stack *b)
{
	int		bs;
	t_stack	*p;

	bs = 0;
	if (b)
		bs = b->size;
	p = b;
	if (a->size >= bs)
		p = a;
	while (p->top)
	{
		st_pop_value(p, &bs);
		ft_print_inst(bs);
	}
	st_free(b);
	return (1);
}

int	ft_sort(t_stack *a, t_stack *old)
{
	t_data	d;
	int		s;

	s = ft_init_data(&d, a);
	if (!s)
		return (0);
	while (d.sorted < s)
	{
		if (st_empty(d.b))
		{
			if (!ft_asort(&d))
				return (ft_free_data(&d));
			d.first_loop = 0;
		}
		else if (!ft_bsort(&d))
			return (ft_free_data(&d));
	}
	if (!st_reverse(&(d.ih)))
		return (ft_free_data(&d));
	ft_print_biggest(d.ih, old);
	return (ft_free_data(&d) + 1);
}

t_stack	*ft_sort_old(t_stack *a)
{
	t_stack	*b;
	t_inst	i;
	t_stack	*ret;

	b = st_new();
	ret = st_new();
	if (!b || !ret)
		return (ft_dummy_sum((int)st_free(a) + (int)st_free(b)
				+ (int)st_free(ret)));
	while (42)
	{
		i = st_evaluate(a, b);
		if (i == END)
			break ;
		i = ft_try_double(b, i);
		if (!ft_execute(i, a, b) || 1)
			return (ft_dummy_sum((int)st_free(a) + (int)st_free(b)
					+ (int)st_free(ret)));
		st_push(ret, i);
	}
	i = (int)st_free(a) + (int)st_free(b);
	if (!st_reverse(&ret))
		return (st_free(ret));
	return (ret);
}
