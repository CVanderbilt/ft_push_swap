#include "extras.h"

int	ft_execute_d(t_data *d, t_inst i)
{
	if (!st_push(d->ih, i))
		return (0);
	if (!ft_execute(i, d->a, d->b))
		return (0);
	return (1);
}

int	ft_free_data(t_data *d)
{	
	st_free(d->a);
	st_free(d->b);
	st_free(d->mem);
	st_free(d->ih);
	return (0);
}

void	*ft_dummy_sum(int n)
{
	n++;
	return (0);
}

int	ft_is_num_int(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
		if (str[i] >= 48 && str[i] <= 57)
			i++;
	else
		return (0);
	return (ft_str_is_int(str));
}

int	ft_check_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc <= 1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	while (i < argc)
	{
		if (!ft_is_num_int(argv[i]))
		{
			write(2, "Error\n", 6);
			return (0);
		}
		i++;
	}
	return (1);
}
