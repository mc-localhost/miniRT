#include "../include/minirt.h"

int	rt_file(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3)
		return (EXIT_FAILURE);
	return (ft_strncmp(file + len - 3, ".rt", 3));
}
