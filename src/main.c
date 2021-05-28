#include "stack.h"
#include "extras.h"

char	**argv_splitter(int argc, char **argv);

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

int	get_argv_size(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void ft_free_arg(char **argv)
{
	int i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

int	main(int argc, char *argvo[])
{
	int		aux;
	t_stack	*st;
	t_stack	*st2;
	t_stack	*old;
	char **argv;

	argv = argv_splitter(argc, argvo);
	argc = get_argv_size(argv);
	if (!ft_check_argv(argc, argv))
		return (1);
	if (init_program(argc, &st, &st2, &old))
		return (1);
	aux = 0;
	while (argv[++aux])
		if (!st_push(st, ft_atoi(argv[aux]))
			|| !st_push(st2, ft_atoi(argv[aux])))
			return ((int)st_free(st) + (int)st_free(st2) + 1);
	ft_free_arg(argv);
	if (!st_reverse(&st) || !st_reverse(&st2))
		return (write(2, "Error\n", 6) + (int)st_free(st) + (int)st_free(st2));
	if (!ft_check_stack(st2))
		return (write(2, "Error\n", 6) + (int)st_free(st) + (int)st_free(st2));
	if (st->size <= 200)
		old = ft_sort_old(st);
	if (ft_sort(st2, old))
		return (0);
	return (1);
}
