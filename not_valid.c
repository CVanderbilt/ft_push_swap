#include "extras.h"

void ft_print_stacks(t_stack *a, t_stack *b)
{
	int h;
	int ha = st_size(a);
	int hb = st_size(b);
	t_stack *adup = st_dup(a);
	t_stack *bdup = st_dup(b);
	
	h = ha > hb? ha : hb;
	for (int i = 0; i < h; i++)
	{
		int aux = h - i;
		if (aux <= ha)
			printf("%2d", st_pop(adup)->value);
		else
			printf("  ");
		if (aux <= hb)
			printf("  %2d\n", st_pop(bdup)->value);
		else
			printf("    \n");
	}
	printf("__  __\n");
	printf("a   b\n");
}