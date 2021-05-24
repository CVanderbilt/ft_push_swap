#include "stack.h"
#include <stdio.h>

int ft_rra(t_stack *a)
{
	//bajar
	/*	
	*	5	3
	*	2	5
	*	8	2
	*	1	8
	*	4	1
	*	3	4
	*/
	t_node *last;
	t_node *aux;
	int size;

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

int ft_ra(t_stack *a)
{
	//subir
	/*	
	*	5	2
	*	2	8
	*	8	1
	*	1	4
	*	4	3
	*	3	5
	*/
	t_node *last;
	t_node *first;
	int size;

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

int ft_pa(t_stack *a, t_stack *b)
{
	t_node *aux;
	
	//aux = st_pop(a);
	aux = st_pop(b);
	if (!aux)
		return (0);
	aux = st_push(a, aux->value);
	if (!aux)
		return (0);
	return (1);
}

int ft_sa(t_stack *a)
{
	t_node *top;
	t_node *second;

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
/*
void ft_print_stacks(t_stack *a, t_stack *b)
{
	int h;
	int ha = st_size(a);
	int hb = st_size(b);
	t_stack *adup = st_dup(a);
	t_stack *bdup = st_dup(b);
	
	h = ha > hb? ha : hb;
	for (int i = 0; i < h; i++)
	{
		int aux = h - i;
		if (aux <= ha)
			printf("%2d", st_pop(adup)->value);
		else
			printf("  ");
		if (aux <= hb)
			printf("  %2d\n", st_pop(bdup)->value);
		else
			printf("    \n");
	}
	printf("__  __\n");
	printf("a   b\n");
}*/

int ft_execute(t_inst inst, t_stack *a, t_stack *b)
{
	if (inst == RB)
		return (ft_ra(b));
	if (inst == RA)
		return (ft_ra(a));
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
	if (inst == RR)
	{
		if (!ft_ra(a))
			return (0);
		return (ft_ra(b));
	}
	return (1);
}