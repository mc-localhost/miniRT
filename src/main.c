/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:42:43 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/21 10:11:01 by vvasiuko         ###   ########.fr       */
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
	scene->camera.fov_rad = scene->camera.fov_deg * (M_PI / 180.f);
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
	scene->spheres[0]->center = (t_vec3){0.f, 0.f, -20.f};
	scene->spheres[0]->diameter = 10.f;
	scene->spheres[0]->r = 5.f; // Radius is diameter / 2
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

static void	init_viewport(t_data *data)
{
	data->viewport_w = 2 * data->focal_len
		* tanf(data->scene->camera.fov_rad / 2);
	data->viewport_h = data->viewport_w / data->aspect_ratio;
	data->viewport_u = (t_vec3){data->viewport_w, 0, 0};
	data->viewport_v = (t_vec3){0, -1 * data->viewport_h, 0};

	printf("viewport_u ={%f, %f, %f}\n", data->viewport_u.x, data->viewport_u.y, data->viewport_u.z);

	data->pixel_delta_u = v_scale(data->viewport_u, 1.f / data->w);
	data->pixel_delta_v = v_scale(data->viewport_v, 1.f / data->h);

	printf("pixel_delta_u ={%f, %f, %f}\n", data->pixel_delta_u.x, data->pixel_delta_u.y, data->pixel_delta_u.z);

	data->scene->camera.view_point = (t_vec3){0.f, 0.f, 0.f}; //change later to account for direction
	data->viewport_u_l = data->scene->camera.view_point;
	v_subtract_inplace(&data->viewport_u_l, (t_vec3){0, 0, data->focal_len});
	v_subtract_inplace(&data->viewport_u_l, v_scale(data->viewport_u, 0.5f));
	v_subtract_inplace(&data->viewport_u_l, v_scale(data->viewport_v, 0.5f));

	printf("viewport_u_l ={%f, %f, %f}\n", data->viewport_u_l.x, data->viewport_u_l.y, data->viewport_u_l.z);

	data->pixel00_loc = data->viewport_u_l;
	v_add_inplace(&data->pixel00_loc, v_scale(data->pixel_delta_u, 0.5f));
	v_add_inplace(&data->pixel00_loc, v_scale(data->pixel_delta_v, 0.5f));

	printf("pixel00_loc ={%f, %f, %f}\n", data->pixel00_loc.x, data->pixel00_loc.y, data->pixel00_loc.z);
}

static int	init_data(t_data *data, char *file)
{
	if (rt_file(file) != 0)
		return (error_message("Error\nwrong file extension: must be .rt"));
	//----- parsing filler ------
	data->scene = (t_scene *)calloc(1, sizeof(t_scene));
	setup_scene(data->scene);
	// --------------------------
	data->w = WIDTH; //can be some check here actually
	data->h = HEIGHT; //can be some check here actually
	data->aspect_ratio = (float)data->w / data->h;
	data->focal_len = 1.f;
	init_viewport(data);
	return (EXIT_SUCCESS);
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
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.size_l, &data.img.endian);
	put_pixels(&data);
	mlx_put_image_to_window(data.mlx, data.window, data.img.img, 0, 0);
	mlx_hook(data.window, 17, 0, clean_exit, &data);
	mlx_hook(data.window, 2, 1L << 0, key_hook, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
