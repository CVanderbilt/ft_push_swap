#include "stack.h"
#include "utils.h"
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

int ft_get_min(t_stack *st, int min, int *ret);

int ft_node_contains_dup(t_node *n)
{
	t_node *aux;
	int num;

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

int ft_check_stack(t_stack *st)
{
	t_node *aux;

	aux = st->top;
	while (aux)
	{
		if (ft_node_contains_dup(aux))
			return (0); //falla
		aux = aux->next;
	}
	return (1);
}

int ft_is_double_inst(t_inst i)
{
	if (i == RR || i == RRR || i == SS)
		return (1);
	return (0);
}

int ft_colapse_inst(t_stack *arr)
{
	if (st_size(arr) < 2)
		return (1);
	if (((arr->top->value == SA && (st_get_node(arr, 1)->value) == SB)) ||
	(arr->top->value == SB && st_get_node(arr, 1)->value == SA))
	{
		st_delete_top(arr);
		st_delete_top(arr);
		if (!st_push(arr, SS))
			return (0);
	}
	if (((arr->top->value == RA) && st_get_node(arr, 1)->value == RB) ||
	(arr->top->value == RB && st_get_node(arr, 1)->value == RA))
	{
		st_delete_top(arr);
		st_delete_top(arr);
		if (!st_push(arr, RR))
			return (0);
	}
	return (1);
}

void ft_print_inst(t_inst i)
{
	if (i == SA)
		write(1, "sa", 2);
	else if (i == SB)
		write(1, "sb", 2);
	else if (i == PA)
		write(1, "pa", 2);
	else if (i == PB)
		write(1, "pb", 2);
	else if (i == RA)
		write(1, "ra", 2);
	else if (i == RB)
		write(1, "rb", 2);
	else if (i == RR)
		write(1, "rr", 2);
	else if (i == SS)
		write(1, "ss", 2);
	else if (i == RRB)
		write(1, "rrb", 3);
	else if (i == RRA)
		write(1, "rra", 3);
	write(1, "\n", 1);
}

int ft_try_double(t_stack *a, t_stack *b, t_stack *arr)
{
	t_inst last;
	t_inst try;
	int min;

	if (!arr->top)
		return (1);
	last = arr->top->value;
	if (last == SA || last == RA)
	{
		ft_get_min(b, -INT_MAX, &min);
		min = st_contains(b, min);
		if (min == 1 && last == SA)
			arr->top->value = SS;
		else if (arr->top->value == RA && min >= st_size(b) / 2)
			arr->top->value = RR;
	}
	return (1);
}

int ft_sort(t_stack *a)
{
	t_stack *b;
	t_stack *arr;

	arr = st_new();
	b = st_new();
	if (!b)
		return (0);
	while (42)
	{	
		if (!st_push(arr, st_evaluate(a, b)))
			return (0);
		if (arr->top->value == END)
		{
			st_delete_top(arr);
			break ;
		}
		ft_try_double(a, b, arr);
		ft_print_inst(arr->top->value);
		if (!ft_execute(arr->top->value, a, b))
			return (0);
	}
	st_reverse(&arr);
	return (1);
}

int main(int argc, char *argv[])
{
	int aux;
	t_stack *st;

	st = st_new();
	if (argc <= 1)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (!st)
		return (1);
	aux = 0;
	while (argv[++aux])
		if (!st_push(st, ft_atoi(argv[aux])));
			return (st_free(st) + 1);
	if (!st_reverse(&st))
		return (st_free(st) + 1);
	if (!ft_check_stack(st))
		return (st_free(st) + 1);
	if (ft_sort(st))
		return (0);
	return (1);
}