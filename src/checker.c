#include "extras.h"
#include <unistd.h>
#include <stdlib.h>

int	get_next_line(char **line)
{
	int		rb;
	char	buff[2];
	char	*ret;

	ret = ft_strdup("");
	buff[1] = 0;
	rb = read(0, buff, 1);
	while (rb > 0)
	{
		if (*buff == '\n')
		{
			*line = ret;
			return (1);
		}
		ret = ft_strjoin(ret, buff, 'L');
		rb = read(0, buff, 1);
	}
	if (rb < 0)
		return (-1);
	*line = ret;
	return (0);
}

int	ft_loop(t_stack *a, t_stack *b)
{
	char	*line;
	t_inst	i;

	while (get_next_line(&line))
	{
		i = get_inst(line);
		free (line);
		if (!ft_execute(i, a, b))
			return (-1);
	}
	if (b->size != 0)
		return (0);
	return (ft_check_st_sorted(a));
}

int	init_program(int argc, t_stack **st, t_stack **st2)
{
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

int	main (int argc, char *argv[])
{
	int		aux;
	t_stack	*a;
	t_stack	*b;

	if (!ft_check_argv(argc, argv))
		return (1);
	if (init_program(argc, &a, &b))
		return (1);
	aux = 0;
	while (argv[++aux])
		if (!st_push(a, ft_atoi(argv[aux])))
			return ((int)st_free(a) + (int)st_free(b) + 1
				+ write(1, "Error\n", 6));
	if (!st_reverse(&a))
		return (write(2, "Error\n", 6) + (int)st_free(a) + (int)st_free(b));
	if (!ft_check_stack(a))
		return (write(2, "Error\n", 6) + (int)st_free(a) + (int)st_free(b));
	aux = ft_loop(a, b);
	if (aux > 0)
		write(1, "OK\n", 3);
	else if (aux == 0)
		write(1, "KO\n", 3);
	else
		return (1 + (int)ft_dummy_sum(write(1, "Error\n", 6)));
	return (0);
}
