#include <stdlib.h>

int	get_argv_size(char **argv, int *aux)
{
	int	i;

	if (aux)
		*aux = 0;
	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ft_free_arg(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
	return (0);
}
