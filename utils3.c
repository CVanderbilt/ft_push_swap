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
