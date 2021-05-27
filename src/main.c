#include "stack.h"
#include "extras.h"

int	init_program(int argc, t_stack **st, t_stack **st2, t_stack **old)
{
	*old = 0;
	if (argc <= 1)
		return ((int)write(2, "Error\n", 6));
	*st = st_new();
	if (!*st)
		return ((int)write(2, "Error\n", 6));
	*st2 = st_new();
	if (!*st)
		return ((int)write(2, "Error\n", 6) + (int)st_free(*st));
	return (0);
}

int	main(int argc, char *argv[])
{
	int		aux;
	t_stack	*st;
	t_stack	*st2;
	t_stack	*old;

	if (!ft_check_argv(argc, argv))
		return (1);
	if (init_program(argc, &st, &st2, &old))
		return (1);
	aux = 0;
	while (argv[++aux])
		if (!st_push(st, ft_atoi(argv[aux]))
			|| !st_push(st2, ft_atoi(argv[aux])))
			return ((int)st_free(st) + (int)st_free(st2) + 1);
	if (!st_reverse(&st) || !st_reverse(&st2))
		return (write(2, "Error\n", 6) + (int)st_free(st) + (int)st_free(st2));
	if (!ft_check_stack(st2))
		return (write(2, "Error\n", 6) + (int)st_free(st) + (int)st_free(st2));
	if (st->size <= 100)
		old = ft_sort_old(st);
	if (old)
		st = old;
	return (ft_sort(st2, old));
}
