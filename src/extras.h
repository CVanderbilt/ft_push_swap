#ifndef EXTRAS_H
# define EXTRAS_H
# include "stack.h"
# include <stdio.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_coordinates
{
	int			x;
	int			y;
}				t_coordinates;

typedef struct s_data
{
	t_stack		*a;
	t_stack		*b;
	int			sorted;
	t_stack		*mem;
	int			first_sorted;
	t_stack		*ih;
	int			stoping;
	int			first_loop;
}				t_data;

int				ft_check_stack(t_stack *st);
int				ft_is_double_inst(t_inst i);
int				ft_get_min(t_stack *st, int min, int *ret);
int				ft_get_max(t_stack *st, int max, int *ret);
int				ft_execute(t_inst inst, t_stack *a, t_stack *b);
void			ft_print_stacks(t_stack *a, t_stack *b);

int				ft_bsort(t_data *d);

t_inst			get_inst(const char *str);

/*
*	sorter
*/

int				ft_sort(t_stack *a, t_stack *old);
t_stack			*ft_sort_old(t_stack *a);

/*
*	asort
*/

int				ft_asort(t_data *d);

/*
*	utils1
*/

int				ft_atoi(const char *str);
int				intmin(int a, int b);
int				set_fs(t_data *d, int n);
void			ft_print_inst(t_inst i);
t_coordinates	coo(int x, int y);

/*
*	utils2
*/
int				ft_get_min_section(t_stack *st, int m, int *r, t_coordinates s);
int				ft_get_median_section(t_stack *st, int start, int end);
int				ft_get_median(t_stack *st);
int				ft_num_is_min(t_stack *st, int n);
int				ft_num_is_min_or_max(t_stack *st, int num);

/*
*	utils3
*/
int				ft_execute_d(t_data *d, t_inst i);
int				ft_free_data(t_data *d);
void			*ft_dummy_sum(int n);
int				ft_check_argv(int argc, char **argv);

/*
*	utils4
*/
int ft_strcmp(const char *s1, const char *s2);

/*
*	utils5
*/
char *ft_append(const char *s1, const char *s2);
char *ft_strdup(const char *str);
char *ft_strjoin(char *s1, char *s2, char c);

/*
*	stacksorter
*/
int				ft_node_sorted(t_stack *a, t_stack *b, int n);
int				ft_str_is_int(const char *str);
int				ft_strlen(const char *str);
int				ft_check_st_sorted(t_stack *st);

#endif