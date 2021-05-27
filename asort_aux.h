#ifndef ASORT_AUX_H
# define ASORT_AUX_H
# include "extras.h"

int		ft_auto_sort(t_data *d);
int		ft_get_stoping_pos(t_data *d, int *stoping, int *stop_at);
int		ft_simple_asort(t_data *d, int aux);
void	ft_fix_stoping(t_data *d, int *stop_at, int aux);
int		ft_reposition(t_data *d, int count);
int		ft_sort_pivot(t_data *d, int pivot, int stop_at);
int		ft_agoto_lessereq(t_data *d, int pivot, int *count, int stop_at);

#endif