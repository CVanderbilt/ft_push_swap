#include "extras.h"

t_inst get_inst3(const char *str)
{
	if (str[0] == 'R' && str[1] == 'R')
	{
		if (str[2] == 'A')
			return (RRA);
		if (str[2] == 'B')
			return (RRB);
		if (str[2] == 'R')
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
		if (str[0] == 'S' && str[1] == 'A')
			return (SA);
		if (str[0] == 'S' && str[1] == 'B')
			return (SB);
		if (str[0] == 'S' && str[1] == 'S')
			return (SS);
		if (str[0] == 'R' && str[1] == 'A')
			return (RA);
		if (str[0] == 'R' && str[1] == 'B')
			return (RB);
		if (str[0] == 'R' && str[1] == 'R')
			return (RR);
		if (str[0] == 'P' && str[1] == 'A')
			return (PA);
		if (str[0] == 'P' && str[1] == 'B')
			return (PB);
	}
	else if (len == 3)
		return (get_inst3(str));
	return (NOTHING);
}