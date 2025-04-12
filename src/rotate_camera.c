/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:19:58 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/12 17:56:16 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/*
rotates the camera left/right (yaw) around the world up (Y) axis
*/
void	rotate_camera_yaw(t_data *data, float angle)
{
	float	x;
	float	z;

	x = data->scene->camera.norm.x;
	z = data->scene->camera.norm.z;
	data->scene->camera.norm.x = x * cosf(angle) - z * sinf(angle);
	data->scene->camera.norm.z = x * sinf(angle) + z * cosf(angle);
	data->scene->camera.norm = v_unit(data->scene->camera.norm);
	data->needs_update = true;
}

/*
rotates the camera up/down (pitch) around the camera's 
right vector (not around the X-axis!)
*/
void	rotate_camera_pitch(t_data *data, float angle)
{
	t_vec3	forward;
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	new_forward;

	forward = data->scene->camera.norm;
	world_up = (t_vec3){0.0f, 1.0f, 0.0f};
	right = v_unit(v_cross(forward, world_up));
	new_forward = v_scale(forward, cosf(angle));
	new_forward.x += (right.y * forward.z - right.z * forward.y) * sinf(angle);
	new_forward.y += (right.z * forward.x - right.x * forward.z) * sinf(angle);
	new_forward.z += (right.x * forward.y - right.y * forward.x) * sinf(angle);
	data->scene->camera.norm = v_unit(new_forward);
	data->needs_update = true;
	if (data->scene->camera.norm.y < -0.99800)
		data->scene->camera.norm.y = 0.98f;
	else if (data->scene->camera.norm.y > 0.99800)
		data->scene->camera.norm.y = -0.98;
	printf("angle: %f, cos: %f, sin: %f\n", angle, cosf(angle), sinf(angle));
	printf("new camera norm: x= %f, y= %f, z= %f\n", data->scene->camera.norm.x,
		data->scene->camera.norm.y, data->scene->camera.norm.z);
}
