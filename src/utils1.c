#include "extras.h"

int	ft_atoi(const char *str)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str++ <= '9')
		ret = *(str - 1) - 48 + 10 * ret;
	return (ret * sign);
}

int	intmin(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

int	set_fs(t_data *d, int n)
{
	if (!d->sorted)
		d->first_sorted = n;
	return (1);
}

void	ft_print_inst(t_inst i)
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

t_coordinates	coo(int x, int y)
{
	t_coordinates	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}
