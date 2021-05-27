#include "extras.h"

int	ft_get_target(t_stack *a, t_stack *b, int min, int *control)
{
	int	m1;
	int	m2;
	int	c1;
	int	c2;

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

t_inst	actions(t_stack *a, t_stack *b, int sid, int target)
{
	int	pos;

	if (sid == 1)
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

t_inst	st_evaluate(t_stack *a, t_stack *b)
{
	int	target;
	int	control;
	int	min;

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
	return (actions(a, b, control, target));
}
