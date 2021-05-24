#include "utils.h"

int	ft_atoi(const char *str)
{
	int ret;
	int sign;

	ret = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		sign = *str++ == '-' ? -1 : 1;
	while (*str >= '0' && *str++ <= '9')
		ret = *(str - 1) - 48 + 10 * ret;
	return (ret * sign);
}

int intmin(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}