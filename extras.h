#ifndef EXTRAS_H
# define EXTRAS_H
# include "stack.h"
# include <stdio.h>
# include <limits.h>
# include <unistd.h>

int ft_check_stack(t_stack *st);
int ft_is_double_inst(t_inst i);
int ft_get_min(t_stack *st, int min, int *ret);
int ft_execute(t_inst inst, t_stack *a, t_stack *b);
void ft_print_stacks(t_stack *a, t_stack *b); //quitar

#endif