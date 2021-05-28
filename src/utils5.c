#include "extras.h"
#include <stdlib.h>

char	*ft_append(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*ret;
	int		error;

	error = 0;
	if (!s1 || !s2)
		return (0);
	ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		error = 1;
	i = -1;
	j = -1;
	while (s1[++i] && !error)
		ret[i] = s1[i];
	while (s2[++j] && !error)
		ret[i + j] = s2[j];
	if (!error)
		ret[i + j] = 0;
	return (ret);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i])
		i++;
	ret = (char *)malloc(i + 1);
	if (!ret)
		return (0);
	i = -1;
	while (str[++i])
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2, char c)
{
	char	*ret;

	ret = ft_append(s1, s2);
	if (c == 'L' || c == 'B')
		free (s1);
	if (c == 'R' || c == 'B')
		free (s2);
	return (ret);
}

int	skip_char(int i, const char *str, char c)
{
	while (str[i] == c)
		i++;
	return (i);
}

int skip_not_char(int i, const char *str, char c)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_strcdup(const char *str, char c)
{
	int		len;
	char 	*ret;

	len = 0;
	while(str[len] && str[len] != c)
		len++;
	ret = (char *)malloc(len + 1);
	len = -1;
	while(str[++len] && str[len] != c)
		ret[len] = str[len];
	ret[len] = 0;
	return (ret);
}

char	**argv_splitter(int argc, char **argv)
{
	t_stack	*st;
	int i;
	int j;
	char **ret;

	st = st_new();
	if  (!st)
		return (0);
	if (!st_push(st, 0))
		 return (st_free_full(st));
	st->top->aux = ft_strdup("push_swap");
	if (!st->top->aux)
		return (st_free_full(st));
	i = 0;
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
