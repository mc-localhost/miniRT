/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:12:00 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/08 13:19:54 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	move_light(t_data *data, t_light *light, float coef, char dir)
{
	float	dist;
	t_vec3	movement;

	dist = coef * data->move_speed;
	if (dir == 'x')
		movement = (t_vec3){dist, 0.0f, 0.0f};
	else if (dir == 'y')
		movement = (t_vec3){0.0f, dist, 0.0f};
	else
		movement = (t_vec3){0.0f, 0.0f, dist};
	v_add_inplace(&light->pos, movement);
	data->needs_update = true;
}

void	move_obj(t_data *data, t_obj *obj, float coef, char dir)
{
	float	dist;
	t_vec3	movement;

	dist = coef * data->move_speed;
	if (dir == 'x')
		movement = (t_vec3){dist, 0.0f, 0.0f};
	else if (dir == 'y')
		movement = (t_vec3){0.0f, dist, 0.0f};
	else if (dir == 'z')
		movement = (t_vec3){0.0f, 0.0f, dist};
	if (obj->type == SPHERE || obj->type == CYLINDER)
		v_add_inplace(&obj->center, movement);
	else if (obj->type == PLANE)
		v_add_inplace(&obj->point, movement);
	data->needs_update = true;
}

void	move_camera_forward(t_data *data, float distance)
{
	t_vec3	forward;
	t_vec3	movement;

	forward = data->scene->camera.norm;
	movement = v_scale(forward, distance);
	v_add_inplace(&data->scene->camera.view_point, movement);
	data->needs_update = true;
}

void	move_camera_sideways(t_data *data, float distance)
{
	t_vec3	forward;
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	movement;

	forward = data->scene->camera.norm;
	world_up = (t_vec3){0.0f, 1.0f, 0.0f};
	right = v_unit(v_cross(forward, world_up));
	movement = v_scale(right, distance);
	v_add_inplace(&data->scene->camera.view_point, movement);
	data->needs_update = true;
}

void	move_camera_vertical(t_data *data, float distance)
{
	t_vec3	forward;
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	up;
	t_vec3	movement;

	forward = data->scene->camera.norm;
	world_up = (t_vec3){0.0f, 1.0f, 0.0f};
	right = v_unit(v_cross(forward, world_up));
	up = v_cross(right, forward);
	movement = v_scale(up, distance);
	v_add_inplace(&data->scene->camera.view_point, movement);
	data->needs_update = true;
}
