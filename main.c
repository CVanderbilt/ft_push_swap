#include "stack.h"
#include "utils.h"
#include "extras.h"

typedef struct 	s_coordinates
{
	int 		x;
	int			y;
}				t_coordinates;

t_coordinates	coo(int x, int y)
{
	t_coordinates ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

typedef struct 	s_data
{
	t_stack 	*a;
	t_stack 	*b;
	int 		sorted;
	t_stack 	*mem;
	int 		first_sorted;
	t_stack 	*ih;
	int 		stoping; //cutrisimo pero bueno :(
	int 		first_loop; //otra cutrez
}				t_data;

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

int ft_get_min_section(t_stack *st, int min, int *res, t_coordinates section)
{
	t_node *start;
	t_node *end;
	int control;

	control = 0;
	start = st_get_node(st, section.x);
	end = st_get_node(st, section.y);
	while (start != end && start) //la segunda condición sobra pero por si las moscas
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

int ft_get_median_section(t_stack *st, int start, int end)
{
	int total;
	int aux;
	int min;

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

int ft_get_median(t_stack *st)
{
	int total;
	int aux;
	int min;

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

t_inst ft_try_double(t_stack *b, t_inst last)
{
	int min;

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

int ft_sort_old(t_stack *a)
{
	t_stack *b;
	t_inst i;

	b = st_new();
	if (!b)
		return ((int)st_free(a));
	while (42)
	{
		i = st_evaluate(a, b);
		if (i == END)
			break ;
		i = ft_try_double(b, i);
		ft_print_inst(i);
		if (!ft_execute(i, a, b))
			return ((int)st_free(a) + (int)st_free(b));
		//ft_print_stacks(a, b);
	}
	return ((int)st_free(a) + (int)st_free(b) + 1);
}

int ft_execute_d(t_data *d, t_inst i)
{
	if (!st_push(d->ih, i))
		return (0);
	if (!ft_execute(i, d->a, d->b))
		return (0);
	//ft_print_inst(i);
	//ft_print_stacks(d->a, d->b);
	return (1);
}

int ft_num_is_min(t_stack *st, int n)
{
	t_node *no;

	no = st->top;
	while (no)
	{
		if (no->value < n)
			return (0);
		no = no->next;
	}
	return (1);
}

int atop_sorted(t_data *d)
{
	int min;

	min = -INT_MAX - 1;
	if (d->sorted)
		min = st_get_node(d->a, d->a->size - 1)->value + 1;
	if (!ft_get_min(d->a, min, &min))
		return (0);
	if (d->a->top->value == min)
		return (1);
	else if (((t_node*)d->a->top->next)->value == min)
	{
		ft_execute_d(d, SA);
		return (1);
	}
	return (0);
}

int ft_agoto_lessereq(t_data *d, int pivot, int *count, int stop_at)
{//de momento solo hace ra pero lo mismo podría hacer también rra si le viene bien
//decreciendo el count y tal
//busca un menor o igual que el pivot y lo lleva con ra a top
//si no lo encuentra devuelve 0, es que ya hemos acabado con todos
	t_node *n;
	int pos;

	pos = 0;
	n = d->a->top;

	while (1)
	{
		if (!n || (d->stoping && n->value == stop_at))
			return (0);
		if (n->value <= pivot)
			break ;
		pos++;
		n = n->next;
	}
	while (pos > 0)
	{
		if (d->a->top->value <= pivot)
			break ;
		ft_execute_d(d, RA);
		*count = *count + 1;
		pos--;
	}
	return (1);
}

int ft_simple_asort3(t_data *d)
{
	t_node *first;
	t_node *second;
	t_node *third;
	int ret;

	first = d->a->top;
	second = first->next;
	third = second->next;
	if (third->value > first->value && first->value > second->value)
	{
		ret = ft_execute_d(d, SA);
		if (!d->sorted)
			d->first_sorted = d->a->top->value;
		ret *= ft_execute_d(d, RA) * ft_execute_d(d, RA) * ft_execute_d(d, RA);
	}
	else if (second->value > first->value && first->value > third->value)
	{
		ret = ft_execute_d(d, PB)  * ft_execute_d(d, SA);
		if (!d->sorted)
			d->first_sorted = d->a->top->value;
		ret *= ft_execute_d(d, RA) * ft_execute_d(d, PA) * ft_execute_d(d, RA) * ft_execute_d(d, RA);
	}
	else if (first->value > second->value && second->value > third->value)
	{
		ret = ft_execute_d(d, PB) * ft_execute_d(d, SA);
		if (!d->sorted)
			d->first_sorted = d->a->top->value;
		ret *= ft_execute_d(d, RA) * ft_execute_d(d, RA) * ft_execute_d(d, PA) * ft_execute_d(d, RA);
	} 
	else// if (first->value > third->value && third->value > second->value)
	{
		ret = ft_execute_d(d, SA);
		if (!d->sorted)
			d->first_sorted = d->a->top->value;
		ret *= ft_execute_d(d, RA) * ft_execute_d(d, SA) * ft_execute_d(d, RA) * ft_execute_d(d, RA);
	}
	d->sorted += 3;
	return (ret);
}

int ft_simple_asort2(t_data *d)
{
	int ret;
		
	ret = 1;
	if (d->a->top->value > ((t_node*)(d->a->top->next))->value)
		ret = ft_execute_d(d, SA);
	if (!d->sorted)
		d->first_sorted = d->a->top->value;
	d->sorted += 2;
	ret *= (ft_execute_d(d, RA) * ft_execute_d(d, RA));
	return (ret);
}

int ft_simple_asort1(t_data *d)
{
	if (!d->sorted)
			d->first_sorted = d->a->top->value;
	d->sorted++;
	return (ft_execute_d(d, RA));
}

int ft_asort(t_data *d)
{
	int pivot;
	int aux;
	int aux2;
	int s;
	t_inst last;
	t_node *n;
	int stoping;
	int stop_at;
	int count;

	d->stoping = 1;
	aux2 = 0;
	while(atop_sorted(d))
	{
		d->sorted++;
		if (d->mem->top && d->mem->top->value == d->a->top->value)
			st_delete_top(d->mem);
		ft_execute_d(d, RA);
	}
	if (d->sorted >= d->a->size)
		return (1);
	while (42)
	{
		stoping = 0;
		if (st_empty(d->mem))
			aux = d->a->size - d->sorted;
		else
		{
			stop_at = st_pop(d->mem)->value;
			aux = st_contains(d->a, stop_at);
			if (aux > 0)
				stoping = 1;
		}
		if (aux < 0)
			return (1); // ?
		if (aux > 0)
			break ;
	}
	//if (stoping)
		//printf("vamos a parar en pos %d\n", aux);
	if (aux == 3)
		return (ft_simple_asort3(d));
	if (aux == 2)
		return (ft_simple_asort2(d));
	if (aux == 1 || ft_num_is_min(d->a, ((t_node*)d->a->top->next)->value))
		return (ft_simple_asort1(d));
	n = st_get_node(d->a, aux);
	if (d->sorted)
		stop_at = d->first_sorted;
	else
	{
		stop_at = st_get_node(d->a, aux - 1)->value;
		d->stoping = 0;
	}
	if (n)
		stop_at = n->value;
	s = d->a->size;
	//pivot = d->a->top->value;
	if (d->stoping)
		pivot = ft_get_median_section(d->a, 0, aux - 1);
	else
		pivot = ft_get_median_section(d->a, 0, aux);
	
	//pivot = ft_get_median(d->a);
	
	//while (aux2 < s)
	//{
	count = 0;
		while(1)
		{//revisar si vamos a encontrar alguno que largar a la otra pila, para ahorrarnos mil movimientos
	
	if (!ft_agoto_lessereq(d, pivot, &count, stop_at))
		break ;
	
			//if(d->a->top->value <= pivot)
			//if (aux2 >= aux)
			//	break ;
			ft_execute_d(d, PB); //lo mandamos al otro lado
			//aux2++;
			//if (aux2 >= aux)
			//	aux2 = aux2;
		}

		//count es el numero de rra que hacer
		// su complementario es el numero de ra que hacer
		// haremos el que sea menor
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
	if (st_size(d->a) - d->sorted > 0)
		if (!st_push(d->mem, d->a->top->value))
			return (0);
	return (1);
}

int ft_simple_bsort3(t_data *d)
{
	//el más alto arriba/descendente
	t_node *first;
	t_node *second;
	t_node *third;
	int ret;

	ret = 1;
	first = d->b->top;
	second = first->next;
	third = second->next;
	if (third->value > first->value && first->value > second->value) //2 1 3 -> 3 2 1 
		ret = (ft_execute_d(d, RRB));
	else if  (third->value > second->value && second->value > first->value) //1 2 3 -> 2 1 3 -> 3 2 1
		ret = ft_execute_d(d, SB) * ft_execute_d(d, RRB);
	else if (first->value > third->value && third->value > second->value) //3 1 2 -> 1 3 2 -> 3 2 1
		ret = ft_execute_d(d, SB) * ft_execute_d(d, RB);
	else if (second->value > third->value && third->value > first->value) //1 3 2 -> 3 2 1
		ret = ft_execute_d(d, RB);
	else if (second->value > first->value && first->value > third->value) //2 3 1 -> 3 2 1
		ret = (ft_execute_d(d, SB));
	if (ret)
	{
		ret = ft_execute_d(d, PA) * ft_execute_d(d, PA) * ft_execute_d(d, PA);
		if (!d->sorted)
			d->first_sorted = d->a->top->value;
		ret *=  ft_execute_d(d, RA) * ft_execute_d(d, RA) * ft_execute_d(d, RA);
	}
	if (ret)
		d->sorted += 3;
	return (ret);
}

int ft_simple_bsort2(t_data *d)
{
	t_node *first;
	t_node *second;
	int ret;

	first = d->b->top;
	second = first->next;
	if (first->value < second->value)
		if (!ft_execute_d(d, SB))
			return (0);
	ret = (ft_execute_d(d, PA) * ft_execute_d(d, PA));
	if (!d->sorted)
		d->first_sorted = d->a->top->value;
	ret *= ft_execute_d(d, RA) * ft_execute_d(d, RA);
	d->sorted += 2;
	return (ret);
}

int ft_simple_bsort(t_data *d)
{
	int ret;

	if (d->b->size == 3)
		return (ft_simple_bsort3(d));
	else if (d->b->size == 2)
		return (ft_simple_bsort2(d));
	else
	{
		ret = (ft_execute_d(d, PA));
		if (!d->sorted)
			d->first_sorted = d->a->top->value;
		ret *= ft_execute_d(d, RA);
		d->sorted++;
	}
	return (ret);
}

int ft_num_is_min_or_max(t_stack *st, int num)
{
	t_node *n;
	int nmin;
	int nmax;

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

int ft_bgoto_greater(t_data *d, int pivot)
{
	t_node *aux;
	int index;
	int first;
	int last;
	int has_first;
	
	//buscamos uno mayor que el pivot
	//si no encontramos hemos acabado
	//buscamos por arriba y por abajo (el primero y el último que cumplan la condición)
	//haremos rb o rrb en función de cual de los dos esté más cerca
	aux = d->b->top;
	index = 0;
	has_first = 0;
	while (aux)
	{
		if (aux->value > pivot)
		{
			if (!has_first)
			{
				has_first = 1;
				first = index;
			}
			last = index;
		}
		aux = aux->next;
		index++;
	}
	if (!has_first) //no encuentra mayor porque ya hemos sacado todos
		return (0);
	// que está más cerca first del principio o last del final?
	if (first <= d->b->size - last)
	{
		//first está más cerca
		while (d->b->top->value <= pivot)
			ft_execute_d(d, RB);
		return (1);
	}
	else
	{
		while (d->b->top->value <= pivot)
			ft_execute_d(d, RRB);
		return (1);
	}
	
}

int ft_bsort(t_data *d)
{
	int aux;
	int pivot;
	int s;
	t_node *n;

	n = d->b->top;
	s = d->b->size;
	aux = 0;
	if (s <= 3)
		return (ft_simple_bsort(d));
	pivot = ft_get_median(d->b);
	if (ft_num_is_min_or_max(d->b, pivot))
	{
			pivot = ((t_node*)n->next)->value;
		if (ft_num_is_min_or_max(d->b, pivot))
			pivot = ((t_node*)(((t_node*)n->next)->next))->value;
	}
	while (ft_bgoto_greater(d, pivot)) // esperamos que nos diga si no hay más
	{
		ft_execute_d(d, PA);
	}
	if (!st_push(d->mem, d->a->top->value))
		return (0);
	return (1);
}

int ft_free_data(t_data *d)
{
	st_free(d->a);
	st_free(d->b);
	st_free(d->mem);
	st_free(d->ih);
	return (0);
}

int ft_collapse(t_stack *st)
{
	t_node *n;
	t_node *prev;

	prev = 0;
	n = st->top;
	while (n)
	{
		if (prev)
		{
			if ((n->value == SA && prev->value == SB) ||
			(n->value == SB && prev->value == SA))
			{
				st_delete_node(st, prev);
				n->value = SS;
			}
			else if ((n->value == RA && prev->value == RB) ||
			(n->value == RB && prev->value == RA))
			{
				st_delete_node(st, prev);
				n->value = RR;
			}
			else if ((n->value == RRA && prev->value == RRB) ||
			(n->value == RRB && prev->value == RRA))
			{
				st_delete_node(st, prev);
				n->value = RRR;
			}
		}
		prev = n;
		n = n->next;
	}
	return (1);
}

int ft_sort(t_stack *a)
{
	//quicksort
	t_data d;
	int s;

	d.first_loop = 1;
	s = st_size(a);
	d.a = a;
	d.mem = st_new();
	d.sorted = 0;
	if (!d.mem)
		return ((int)st_free(a));
	d.b = st_new();
	if (!d.b)
		return ((int)st_free(d.mem) + (int)st_free(d.a));
	d.ih = st_new();
	if (!d.ih)
		return ((int)st_free(d.mem) + (int)st_free(d.a) + (int)st_free(d.b));
	while (42)
	{
		if (d.sorted >= s)
			break ;
		if (st_empty(d.b))
		{
			//como b está vacío hacemos un sort mandando cosas a b
			if (!ft_asort(&d))
				return (ft_free_data(&d));
			d.first_loop = 0;
		}
		else
		{
			//como b no está vacío hacemos un sort mandando cosas a a
			if (!ft_bsort(&d))
				return (ft_free_data(&d));
		}
	}
	int size_h = d.ih->size;
	if (!st_reverse(&(d.ih)) /*|| !ft_collapse(d.ih)*/)
		return (ft_free_data(&d));
	size_h = d.ih->size;
	while(d.ih->top)
		ft_print_inst(st_pop(d.ih)->value);
	return (ft_free_data(&d) + 1);
}

int main(int argc, char *argv[])
{
	int aux;
	t_stack *st;

	if (argc <= 1)
		return ((int)write(1, "Error\n", 6));
	st = st_new();
	if (!st)
		return ((int)write(1, "Error\n", 6));
	aux = 0;
	while (argv[++aux])
		if (!st_push(st, ft_atoi(argv[aux])))
			return ((int)st_free(st) + 1);
	if (!st_reverse(&st))
		return ((int)st_free(st) + 1);
	if (!ft_check_stack(st))
		return ((int)write(1, "Error\n", 6) + (int)st_free(st));
	if (st->size > 0)
	{
		if (ft_sort(st))
			return (0);
	}
	else if (ft_sort_old(st))
		return (0);
	return ((int)write(1, "Error\n", 6));
}