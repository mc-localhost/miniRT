/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:19:58 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/08 15:02:12 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/*
rotates the camera left/right (yaw) around the world up (Y) axis
*/

void rotate_camera_yaw(t_data *data, float angle)
{
	float x;
	float z;

	x = data->scene->camera.norm.x;
	z = data->scene->camera.norm.z;
	//equation is: NEW VECTOR = ROTATION MATRIX ⋅ ORIGINAL VECTOR
	data->scene->camera.norm.x = x * cosf(angle) - z * sinf(angle);
	data->scene->camera.norm.z = x * sinf(angle) + z * cosf(angle);
	data->scene->camera.norm = v_unit(data->scene->camera.norm);
	data->needs_update = true;
}

/*
rotates the camera up/down (pitch) around the camera's right vector (not around the X-axis!)
*/
void rotate_camera_pitch(t_data *data, float angle)
{
	t_vec3 forward = data->scene->camera.norm;
	t_vec3 world_up = (t_vec3){0.0f, 1.0f, 0.0f}; // we need it to get the camera's right vector
	t_vec3 right = v_unit(v_cross(forward, world_up)); // here it is
	t_vec3 new_forward;

	// simplified implementation of Rodrigue's Rotation Formula (still don't understand its derivation)
	new_forward = v_scale(forward, cosf(angle));
	//the rest can also be modified using v_cross etc. if needed for norm
	new_forward.x += (right.y * forward.z - right.z * forward.y) * sinf(angle);
    new_forward.y += (right.z * forward.x - right.x * forward.z) * sinf(angle);
    new_forward.z += (right.x * forward.y - right.y * forward.x) * sinf(angle);
	data->scene->camera.norm = v_unit(new_forward);
    data->needs_update = true;
	printf("angle: %f, cos: %f, sin: %f\n", angle, cosf(angle), sinf(angle));
	printf("new camera norm: x= %f, y= %f, z= %f\n", data->scene->camera.norm.x, data->scene->camera.norm.y, data->scene->camera.norm.z);
}
