/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:19:58 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/10 16:53:45 by ykhattab         ###   ########.fr       */
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
	t_vec3 forward = data->scene->camera.norm; // that's what we have
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
	if (data->scene->camera.norm.y < -0.99800)
		data->scene->camera.norm.y = 0.98f;
	else if (data->scene->camera.norm.y > 0.99800)
		data->scene->camera.norm.y = -0.98;
	
	printf("angle: %f, cos: %f, sin: %f\n", angle, cosf(angle), sinf(angle));
	printf("new camera norm: x= %f, y= %f, z= %f\n", data->scene->camera.norm.x, data->scene->camera.norm.y, data->scene->camera.norm.z);
}

// AI version
// void rotate_camera_pitch(t_data *data, float angle)
// {
//     t_vec3 forward = data->scene->camera.norm;
//     t_vec3 world_up = (t_vec3){0.0f, 1.0f, 0.0f};
//     t_vec3 right, new_forward;
    
//     // Check if we're about to pass through a vertical position
//     float current_y = forward.y;
//     float potential_y = current_y + sinf(angle) * sqrtf(1.0f - current_y * current_y);
    
//     // If we'd cross the vertical position (y=±1), jump past it
//     if ((current_y < 0.99f && potential_y > 0.99f) || 
//         (current_y > -0.99f && potential_y < -0.99f)) {
        
//         // Calculate a right vector that will stay consistent
//         if (fabsf(forward.z) < 0.0001f && fabsf(forward.x) < 0.0001f) {
//             // If we're exactly at the pole, use a fixed reference
//             right = (t_vec3){1.0f, 0.0f, 0.0f}; 
//         } else {
//             right = v_unit(v_cross(forward, world_up));
//         }
        
//         // Calculate the new forward vector by flipping across the vertical
//         float sign = (current_y > 0) ? -1.0f : 1.0f;
        
//         // Set to a vector slightly past the pole
//         new_forward = (t_vec3){
//             -forward.x * 0.2f,  // Flip and reduce X component
//             sign * 0.98f,       // Set Y to almost ±1 (slightly past pole)
//             -forward.z * 0.2f   // Flip and reduce Z component
//         };
//     } else {
//         // Normal case - compute right vector and apply rotation
//         right = v_unit(v_cross(forward, world_up));
        
//         // Apply Rodrigues' rotation formula
//         new_forward = v_scale(forward, cosf(angle));
//         new_forward.x += (right.y * forward.z - right.z * forward.y) * sinf(angle);
//         new_forward.y += (right.z * forward.x - right.x * forward.z) * sinf(angle);
//         new_forward.z += (right.x * forward.y - right.y * forward.x) * sinf(angle);
//     }
    
//     data->scene->camera.norm = v_unit(new_forward);
//     data->needs_update = true;
    
//     printf("new camera norm: x= %f, y= %f, z= %f\n", 
//            data->scene->camera.norm.x, 
//            data->scene->camera.norm.y, 
//            data->scene->camera.norm.z);
// }