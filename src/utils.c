/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:13 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/20 10:43:13 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_obj	*create_object(t_type type, t_vec3 center, t_colour colour, t_vec3 norm,
		float diameter, float h)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->center = center;
	obj->colour = colour;
	obj->norm = norm;
	obj->diameter = diameter;
	obj->r = diameter / 2.f;
	obj->h = h;
	obj->next = NULL;
	return (obj);
}

void	add_object(t_obj **list, t_obj *new_obj)
{
	t_obj	*temp;

	if (!*list)
	{
		*list = new_obj;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_obj;
}

void	setup_scene(t_scene *scene) //some chatGPT filler while parsing is not there
{
	// Ambient light setup
	scene->a_light.colour = (t_colour){255, 255, 255, 0.2f};
	// Camera setup
	scene->camera = (t_camera){.view_point = (t_vec3){-50.f, 0.f, 20.f},
		.norm = (t_vec3){0.f, 0.f, 0.f}, .fov_deg = 70};
	scene->camera.fov_rad = scene->camera.fov_deg * (M_PI / 180.f);
	// Light setup
	scene->light = (t_light){.pos = (t_vec3){-40.f, 0.f, 30.f},
		.colour = (t_colour){255, 255, 255, 0.7f}};
	// Initialize object list
	scene->objects = NULL;
	// Plane setup
	add_object(&scene->objects, create_object(PLANE, (t_vec3){0.f, 0.f, 0.f},
			(t_colour){255, 0, 225, 1.f}, (t_vec3){0.f, 1.f, 0.f}, 0.f, 0.f));
	// Sphere setups
	add_object(&scene->objects, create_object(SPHERE, (t_vec3){0.f, 0.f, -20.f},
			(t_colour){255, 56, 0, 1.f}, (t_vec3){0.f, 0.f, 0.f}, 10.f, 0.f));
	add_object(&scene->objects, create_object(SPHERE, (t_vec3){10.f, 10.f,
			-40.f}, (t_colour){0, 255, 100, 1.f}, (t_vec3){0.f, 0.f, 0.f}, 18.f,
			0.f));
	add_object(&scene->objects, create_object(SPHERE, (t_vec3){0.f, -2.f,
			-10.f}, (t_colour){50, 100, 255, 1.f}, (t_vec3){0.f, 0.f, 0.f}, 2.f,
			0.f));
	// Cylinder setup
	add_object(&scene->objects, create_object(CYLINDER, (t_vec3){50.f, 0.f,
			20.6}, (t_colour){10, 0, 255, 1.f}, (t_vec3){0.f, 0.f, 1.f}, 14.2f,
			21.42f));
}

/*		PREV VERSION	*/

// static void	setup_scene(t_scene *scene)
// {
// 	// Ambient light setup
// 	scene->a_light.colour = (t_colour){255, 255, 255, 0.2f};
// 	// Camera setup
// 	scene->camera = (t_camera){
// 		.view_point = (t_vec3){-50.f, 0.f, 20.f},
// 		.norm = (t_vec3){0.f, 0.f, 0.f},
// 		.fov_deg = 70
// 	};
// 	scene->camera.fov_rad = scene->camera.fov_deg * (M_PI / 180.f);
// 	// Light setup
// 	scene->light = (t_light){
// 		.pos = (t_vec3){-40.f, 0.f, 30.f},
// 		.colour = (t_colour){255, 255, 255, 0.7f}
// 	};
// 	// Plane setup
// 	scene->num_pl = 1;
// 	scene->planes = malloc(sizeof(t_plane *) * scene->num_pl);
// 	scene->planes[0] = malloc(sizeof(t_plane));
// 	*scene->planes[0] = (t_plane){
// 		.point = (t_vec3){0.f, 0.f, 0.f},
// 		.norm = (t_vec3){0.f, 1.f, 0.f},
// 		.colour = (t_colour){255, 0, 225, 1.f}
// 	};
// 	// Sphere setup
// 	scene->num_sp = 3;
// 	scene->spheres = malloc(sizeof(t_sphere *) * scene->num_sp);

// 	scene->spheres[0] = malloc(sizeof(t_sphere));
// 	scene->spheres[0]->center = (t_vec3){0.f, 0.f, -20.f};
// 	scene->spheres[0]->diameter = 10.f;
// 	scene->spheres[0]->r = scene->spheres[0]->diameter / 2;
		// Radius is diameter / 2
// 	scene->spheres[0]->colour = (t_colour){255, 56, 0, 1.f};

// 	scene->spheres[1] = malloc(sizeof(t_sphere));
// 	scene->spheres[1]->center = (t_vec3){10.f, 10.f, -40.f};
// 	scene->spheres[1]->diameter = 18.f;
// 	scene->spheres[1]->r = scene->spheres[1]->diameter / 2;
		// Radius is diameter / 2
// 	scene->spheres[1]->colour = (t_colour){0, 255, 100, 1.f};

// 	scene->spheres[2] = malloc(sizeof(t_sphere));
// 	scene->spheres[2]->center = (t_vec3){0.f, -2.f, -10.f};
// 	scene->spheres[2]->diameter = 2.f;
// 	scene->spheres[2]->r = scene->spheres[2]->diameter / 2;
		// Radius is diameter / 2
// 	scene->spheres[2]->colour = (t_colour){50, 100, 255, 1.f};

// 	// Cylinder setup
// 	scene->num_cy = 1;
// 	scene->cylinders = malloc(sizeof(t_cylinder *) * scene->num_cy);
// 	scene->cylinders[0] = malloc(sizeof(t_cylinder));
// 	*scene->cylinders[0] = (t_cylinder){
// 		.center = (t_vec3){50.f, 0.f, 20.6},
// 		.norm = (t_vec3){0.f, 0.f, 1.f},
// 		.diameter = 14.2f,
// 		.r = 7.1f,
// 		.h = 21.42f,
// 		.colour = (t_colour){10, 0, 255, 1.f}
// 	};
// }