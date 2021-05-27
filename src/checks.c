#include "stack.h"

int	ft_node_contains_dup(t_node *n)
{
	int	num;

	if (!n)
		return (0);
	num = n->value;
	n = n->next;
	while (n)
	{
		if (n->value == num)
			return (1);
		n = n->next;
	}
	return (0);
}

int	ft_check_stack(t_stack *st)
{
	t_node	*aux;

	aux = st->top;
	while (aux)
	{
		if (ft_node_contains_dup(aux))
			return (0);
		aux = aux->next;
	}
	return (1);
}

int	ft_is_double_inst(t_inst i)
{
	if (i == RR || i == RRR || i == SS)
		return (1);
	return (0);
}
