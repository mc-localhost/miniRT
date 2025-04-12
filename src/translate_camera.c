/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:12:00 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/12 17:57:20 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
