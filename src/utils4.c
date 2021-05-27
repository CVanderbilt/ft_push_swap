#include "extras.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if ((!s1 && !s2))
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_str_is_int(const char *str)
{
	const char	*cmp;
	int			len;
	int			cmp_len;
	int			i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-')
		cmp = "-2147483648";
	else
		cmp = "2147483647";
	cmp_len = ft_strlen(cmp);
	len = ft_strlen(str);
	if (len < cmp_len)
		return (1);
	if (len > cmp_len)
		return (0);
	while (i < len)
	{
		if (str[i] > cmp[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_st_sorted(t_stack *st)
{
	t_node	*n;
	int		prev;
	int		control;

	control = 1;
	n = st->top;
	while (n)
	{
		if (control || prev < n->value)
		{
			prev = n->value;
			control = 0;
		}
		else
			return (0);
		n = n->next;
	}
	return (1);
}
