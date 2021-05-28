#ifndef STACK_H
# define STACK_H
# include <stdio.h>

typedef enum e_inst
{
	NOTHING,
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	PASA,
	SARA,
	SBPA,
	END
}				t_inst;

typedef struct s_node
{
	int			value;
	void		*next;
	char		*aux;
}				t_node;

typedef struct s_stack
{
	t_node		*top;
	int			size;
}				t_stack;

t_stack			*st_new(void);
unsigned int	st_size(t_stack *stack);

t_node			*st_pop(t_stack *st);
t_node			*st_push(t_stack *st, int value);
void			st_delete_top(t_stack *st);

t_inst			st_evaluate(t_stack *a, t_stack *b);
int				st_empty(t_stack *st);
void			st_print(t_stack *st);
int				st_reverse(t_stack **st);
int				st_contains(t_stack *st, int n);
t_node			*st_find(t_stack *st, int n);
t_node			*st_get_node(t_stack *st, int n);
void			st_delete_pos(t_stack *st, int n);
void			st_delete_node(t_stack *st, t_node *n);
t_stack			*st_dup(t_stack *st);
int				st_pop_value(t_stack *st, int *n);

void			*st_free(t_stack *st);

#endif