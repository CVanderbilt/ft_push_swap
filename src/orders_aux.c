#include "extras.h"

t_inst get_inst3(const char *str)
{
	if (str[0] == 'r' && str[1] == 'r')
	{
		if (str[2] == 'a')
			return (RRA);
		if (str[2] == 'b')
			return (RRB);
		if (str[2] == 'r')
			return (RRR);
	}
	return (NOTHING);
}

t_inst get_inst(const char *str)
{
	int len;

	len = ft_strlen(str);
	if (len == 2)
	{
		if (str[0] == 's' && str[1] == 'a')
			return (SA);
		if (str[0] == 's' && str[1] == 'b')
			return (SB);
		if (str[0] == 's' && str[1] == 's')
			return (SS);
		if (str[0] == 'r' && str[1] == 'a')
			return (RA);
		if (str[0] == 'r' && str[1] == 'b')
			return (RB);
		if (str[0] == 'r' && str[1] == 'r')
			return (RR);
		if (str[0] == 'p' && str[1] == 'a')
			return (PA);
		if (str[0] == 'p' && str[1] == 'b')
			return (PB);
	}
	else if (len == 3)
		return (get_inst3(str));
	return (NOTHING);
}