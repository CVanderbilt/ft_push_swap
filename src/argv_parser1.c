#include "extras.h"
#include <stdlib.h>

int	skip_char(int i, const char *str, char c)
{
	while (str[i] == c)
		i++;
	return (i);
}

int	skip_not_char(int i, const char *str, char c)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_strcdup(const char *str, char c)
{
	int		len;
	char	*ret;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	ret = (char *)malloc(len + 1);
	len = -1;
	while (str[++len] && str[len] != c)
		ret[len] = str[len];
	ret[len] = 0;
	return (ret);
}

char	**argv_splitter_aux(t_stack *st)
{
	int		i;
	int		j;
	char	**ret;

	if (!st_reverse(&st))
		return (st_free_full(st));
	ret = (char **)malloc(sizeof(char *) * (st->size + 1));
	if (!ret)
		return (st_free_full(st));
	i = 0;
	j = st->size;
	while (i < j)
	{
		ret[i] = st->top->aux;
		st_pop_value(st, 0);
		i++;
	}
	st_free(st);
	ret[i] = 0;
	return (ret);
}

char	**argv_splitter(int argc, char **argv, int i, int j)
{
	t_stack	*st;

	st = st_new();
	if (!st || !st_push(st, 0))
		 return (st_free_full(st));
	st->top->aux = ft_strdup("push_swap");
	if (!st->top->aux)
		return (st_free_full(st));
	while (++i < argc)
	{
		j = 0;
		while (1)
		{
			j = skip_char(j, argv[i], ' ');
			if (!argv[i][j])
				break ;
			if (!st_push(st, i))
				return (st_free_full(st));
			st->top->aux = ft_strcdup(argv[i] + j, ' ');
			if (!st->top->aux)
				return (st_free_full(st));
			j = skip_not_char(j, argv[i], ' ');
		}
	}
	return (argv_splitter_aux(st));
}
