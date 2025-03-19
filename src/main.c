#include "../include/minirt.h"

static int init_data(t_data *data, char *file)
{
	if (rt_file(file) != 0)
		return(error_message("Error\nwrong file extension: must be .rt\n"));
	//----- parsing ------
	data->w = WIDTH; //can be some check here actually
	data->h = HEIGHT; //can be some check here actually
	data->aspect_ratio = data->w / data->h;
	return(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data		data;

	if (argc != 2)
		return (error_message("Error\nput .rt path after ./miniRT\n"));
	if (init_data(&data, argv[1]) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, data.w, data.h, "miniRT");
	data.img.img = mlx_new_image(data.mlx, data.w, data.h);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.size_l, &data.img.endian);
	// magic
	mlx_hook(data.window, 17, 0, clean_exit, &data);
	mlx_loop(data.mlx);
	return(EXIT_SUCCESS);
}
