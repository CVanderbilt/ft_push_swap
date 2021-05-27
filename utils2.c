#include "extras.h"

int	ft_get_min_section(t_stack *st, int min, int *res, t_coordinates section)
{
	t_node	*start;
	t_node	*end;
	int		control;

	control = 0;
	start = st_get_node(st, section.x);
	end = st_get_node(st, section.y);
	while (start != end && start)
	{
		if (start->value >= min)
		{
			if (!control || start->value < *res)
			{
				*res = start->value;
				control = 1;
			}
		}
		start = start->next;
	}
	return (control);
}

int	ft_get_median_section(t_stack *st, int start, int end)
{
	int	total;
	int	aux;
	int	min;

	if (start < 0)
		start = 0;
	if (end >= st->size)
		end = st->size - 1;
	aux = 0;
	min = -INT_MAX - 1;
	total = (end - start) / 2 + (end - start) % 2;
	total = st->size / 2 + st->size % 2;
	while (aux < total)
	{
		ft_get_min_section(st, min, &min, coo(start, end));
		min++;
		aux++;
	}
	return (min - 1);
}

int	ft_get_median(t_stack *st)
{
	int	total;
	int	aux;
	int	min;

	aux = 0;
	min = -INT_MAX - 1;
	total = st->size / 2 + st->size % 2;
	while (aux < total)
	{
		ft_get_min(st, min, &min);
		min++;
		aux++;
	}
	return (min - 1);
}

int	ft_num_is_min(t_stack *st, int n)
{
	t_node	*no;

	no = st->top;
	while (no)
	{
		if (no->value < n)
			return (0);
		no = no->next;
	}
	return (1);
}

int	ft_num_is_min_or_max(t_stack *st, int num)
{
	t_node	*n;
	int		nmin;
	int		nmax;

	nmin = 1;
	nmax = 1;
	n = st->top;
	while (n && (nmin || nmax))
	{
		if (n->value < num)
			nmin = 0;
		else if (n->value > num)
			nmax = 0;
		n = n->next;
	}
	return (nmin || nmax);
}
