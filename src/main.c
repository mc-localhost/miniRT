/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:42:43 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/20 10:42:45 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

// some chatGPT filler while parsing is not there
static void	setup_scene(t_scene *scene)
{
	// Ambient light setup
	scene->a_light.colour = (t_colour){255, 255, 255, 0.2f};

	// Camera setup
	scene->camera = (t_camera){
		.view_point = (t_vec3){-50.f, 0.f, 20.f},
		.norm = (t_vec3){0.f, 0.f, 0.f},
		.fov_deg = 70
	};
	scene->camera.fov_rad = scene->camera.fov_deg * (M_PI / 180.0f);

	// Light setup
	scene->light = (t_light){
		.pos = (t_vec3){-40.f, 0.f, 30.f},
		.colour = (t_colour){255, 255, 255, 0.7f}
	};

	// Plane setup
	scene->num_pl = 1;
	scene->planes = malloc(sizeof(t_plane *) * scene->num_pl);
	scene->planes[0] = malloc(sizeof(t_plane));
	*scene->planes[0] = (t_plane){
		.point = (t_vec3){0.f, 0.f, 0.f},
		.norm = (t_vec3){0.f, 1.f, 0.f},
		.colour = (t_colour){255, 0, 225, 1.f}
	};

	// Sphere setup
	scene->num_sp = 1;
	scene->spheres = malloc(sizeof(t_sphere *) * scene->num_sp);
	scene->spheres[0] = malloc(sizeof(t_sphere));
	scene->spheres[0]->center = (t_vec3){0.f, 0.f, 20.f};
	scene->spheres[0]->diameter = 20.f;
	scene->spheres[0]->r = 10.f; // Radius is diameter / 2
	scene->spheres[0]->colour = (t_colour){255, 0, 0, 1.f};

	// Cylinder setup
	scene->num_cy = 1;
	scene->cylinders = malloc(sizeof(t_cylinder *) * scene->num_cy);
	scene->cylinders[0] = malloc(sizeof(t_cylinder));
	*scene->cylinders[0] = (t_cylinder){
		.center = (t_vec3){50.f, 0.f, 20.6},
		.norm = (t_vec3){0.f, 0.f, 1.f},
		.diameter = 14.2f,
		.r = 7.1f,
		.h = 21.42f,
		.colour = (t_colour){10, 0, 255, 1.f}
	};
}

static int init_data(t_data *data, char *file)
{
	if (rt_file(file) != 0)
		return(error_message("Error\nwrong file extension: must be .rt\n"));
	//----- parsing filler ------
	data->scene = (t_scene *)calloc(1, sizeof(t_scene));
	setup_scene(data->scene);
	// --------------------------
	data->w = WIDTH; //can be some check here actually
	data->h = HEIGHT; //can be some check here actually
	data->aspect_ratio = (float)data->w / data->h;
	data->focal_length = 1.f;
	data->viewport_h = data->viewport_w / data->aspect_ratio;
	data->viewport_w = 2 * data->focal_length * tanf(data->scene->camera.fov_rad / 2);
	data->viewport_u = (t_vec3){data->viewport_w, 0, 0};
    data->viewport_v = (t_vec3){0, -1 * data->viewport_h, 0};
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
	put_pixels(&data);
	mlx_put_image_to_window(data.mlx, data.window, data.img.img, 0, 0);
	mlx_hook(data.window, 17, 0, clean_exit, &data); //cross button
	mlx_hook(data.window, 2, 1L<<0, key_hook, &data);
	mlx_loop(data.mlx);
	return(EXIT_SUCCESS);
}
