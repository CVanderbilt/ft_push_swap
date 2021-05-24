#include "stack.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int 	st_reverse(t_stack **st)
{
	t_stack *ret;
	t_node *aux;
	t_node *control;

	ret = st_new();
	int i = 0;
	while (42)
	{
		i++;
		aux = st_pop(*st);
		if (!aux)
			break ;
		control = st_push(ret, aux->value);
		free (aux);
		if (!control)
			return (0);
	}
	free (*st);
	*st = ret;
	return (1);
}

int 	st_empty(t_stack *st)
{
	if (st->top)
		return (0);
	return (1);
}

int		ft_get_min(t_stack *st, int min, int *ret)
{
	t_node *aux;
	int control;

	control = 1;
	aux = st->top;
	while (aux)
	{
		if (aux->value >= min)
		{
			if (control || aux->value < *ret)
			{
				control = 0;
				*ret = aux->value;
			}
		}
		aux = aux->next;
	}
	if (!control)
		return (1);
	return (0);
}

int		ft_get_target(t_stack *a, t_stack *b, int min, int *control)
{
	int m1;
	int m2;
	int c1;
	int c2;
	
	c1 = ft_get_min(a, min, &m1);
	c2 = ft_get_min(b, min, &m2);

	if (!c1 && !c2)
	{
		//no ha encontrado otro mínimo, asumimos end
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
	

	//si está bien colocado busca el siguiente, si no hay un siguiente devuelve ese
	//y pone control a 0, sirve para que evaluate sepa que tiene que salir
	//sy lo encuentra pondrá en control 1 si la pila que lo contiene es a y 2 si es b
}

int ft_node_sorted(t_stack *a, t_stack *b, int n)
{
	//node está en su sitio(ordenado) si todos los nodes siguientes
	// son mayores que él y además están también ordenados
	// y además encima no tiene ningún nodo menor que él
	t_node *aux;
	int pre_small;
	int post_big;
	int small_missing;
	int auxn;

	//todos los primeros nodos mayores que n hasta uno que no lo es, desde el cual
	//todos los siguientes son ascendentes (incluyendo a n)
	//todos los nodos de b tienen que ser superiores a n
	//todos los nodos por debajo de n tienen que ser menores que todos los nodos por encima de n
	//->a partir de n tienen que estar en orden ascendente y el más grande de ellos tiene que ser
	//más pequeño que el más pequeño de los previos
	small_missing = 1;
	aux = a->top;
	while (aux && aux->value > n)
	{
		if (small_missing || pre_small > aux->value)
			pre_small = aux->value;
		small_missing = 0;
		aux = aux->next;
	}
	if (ft_get_min(b, -INT_MAX - 1, &auxn))
		if (small_missing || auxn < pre_small)
		{
			small_missing = 0;
			pre_small = auxn;
		}
	//pre_small es el más pequeño de los previos, tendrá
	//que ser más grande que el más grande de los posteriores
	if (!aux)
		return (1);
	post_big = aux->value;
	while (aux)
	{
		if (post_big > aux->value)
			return (0);
		post_big = aux->value;
		aux = aux->next;
	}
	if (small_missing || post_big < pre_small)
		return (1);
	return (0);
}

t_inst	st_evaluate(t_stack *a, t_stack *b)
{
	int target;
	int control;
	int pos;
	int min;
	t_node *aux;

	//si get target devuelve la posición del siguiente a buscar
	//en control está si se acaba o la pila en la que está
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
	if (control == 1)
	{	//está en a
		pos = st_contains(a, target);
		if (pos == 0)
			return (RA);
		if (pos == 1)
			return (SA);
		return (PB);
	}
	else //control == 2
	{	//está en b
		pos = st_contains(b, target);
		if (pos == 0)
			return (PA);
		if (pos == 1)
			return (SB);
		if (pos >= st_size(b) / 2) //aquí ponía target pero no tiene demasiado sentido
			return (RRB);
		return (RB);
		//en verdad lo ideal sería que en caso de que fueran iguales size/2 == target
		//hicieramos rb o rrb según la orden anterior, si es ra lo suyo sería hacer rb para
		//simplificar a rr, si es rra haremos rrb para simplificar a rrr
		//para e
	}
}

/*
void 	st_print(t_stack *st)
{
	t_node *aux;

	aux = st->top;
	while (aux)
	{
		printf("%d\n", (aux->value));
		aux = aux->next;
	}
}*/