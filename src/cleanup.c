#include "../include/minirt.h"

int clean_exit(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
		free(data->mlx);
	// + free everything else before exiting
	exit(0);
}
