#include "stack.h"
#include "extras.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_rra(t_stack *a)
{
	t_node	*last;
	t_node	*aux;
	int		size;

	size = st_size(a);
	if (size <= 1)
		return (1);
	last = st_get_node(a, size - 1);
	aux = st_get_node(a, size - 2);
	last->next = a->top;
	a->top = last;
	aux->next = 0;
	return (1);
}

int	ft_ra(t_stack *a)
{
	t_node	*last;
	t_node	*first;
	int		size;

	size = st_size(a);
	if (size <= 1)
		return (1);
	first = a->top;
	last = st_get_node(a, size - 1);
	last->next = first;
	a->top = first->next;
	first->next = 0;
	return (1);
}

int	ft_pa(t_stack *a, t_stack *b)
{
	t_node	*aux;
	t_node	*control;

	aux = st_pop(b);
	if (!aux)
		return (0);
	control = st_push(a, aux->value);
	free (aux);
	if (!control)
		return (0);
	return (1);
}

int	ft_sa(t_stack *a)
{
	t_node	*top;
	t_node	*second;

	if (st_size(a) > 1)
	{
		top = a->top;
		second = top->next;
		top->next = second->next;
		second->next = top;
		a->top = second;
	}
	return (1);
}

int	ft_execute(t_inst inst, t_stack *a, t_stack *b)
{
	if (inst == RB)
		return (ft_ra(b));
	if (inst == RA)
		return (ft_ra(a));
	if (inst == RRA)
		return (ft_rra(a));
	if (inst == RRB)
		return (ft_rra(b));
	if (inst == SA)
		return (ft_sa(a));
	if (inst == SB)
		return (ft_sa(b));
	if (inst == PA)
		return (ft_pa(a, b));
	if (inst == PB)
		return (ft_pa(b, a));
	if (inst == SS)
	{
		if (!ft_sa(a))
			return (0);
		return (ft_sa(b));
	}
	if (!ft_ra(a))
		return (0);
	return (ft_ra(b));
}
