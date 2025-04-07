/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:00:55 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/07 08:21:28 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	key_hook(int key, t_data *data)
{
	if (key == KEY_ESC)
        clean_exit(data);
        
    // WASD for XZ plane, Q/E for Y axis
    if (key == KEY_W)            // forward
        move_camera_forward(data, data->move_speed);
    else if (key == KEY_S)       // backward
        move_camera_forward(data, -data->move_speed);
    else if (key == KEY_A)       // left
        move_camera_sideways(data, -data->move_speed);
    else if (key == KEY_D)       // right
        move_camera_sideways(data, data->move_speed);
    else if (key == KEY_Q)       // up
        move_camera_vertical(data, data->move_speed);
    else if (key == KEY_E)       // down
        move_camera_vertical(data, -data->move_speed);
	/* arrow keys for camera rotation */
	else if (key == KEY_LEFT)
        rotate_camera_yaw(data, -data->rotate_speed);
    else if (key == KEY_RIGHT)
        rotate_camera_yaw(data, data->rotate_speed);
    else if (key == KEY_UP)
        rotate_camera_pitch(data, data->rotate_speed);
    else if (key == KEY_DOWN)
        rotate_camera_pitch(data, -data->rotate_speed);
	/* ------------------------------ */
	// object rotation functions (could be cleaned and DRYed later)
	else if (key == KEY_NUM_8 && data->selected_object)  // rotate x+
	{
		if (data->selected_object->type == PLANE || data->selected_object->type == CYLINDER)
		{
			rotate_object_x(data->selected_object, 0.1f);
			data->needs_update = true; // i may move this line inside the function
		}
	}
	else if (key == KEY_NUM_2 && data->selected_object)  // rotate x-
	{
		if (data->selected_object->type == PLANE || data->selected_object->type == CYLINDER)
		{
			rotate_object_x(data->selected_object, -0.1f);
			data->needs_update = true;
		}
	}
	else if (key == KEY_NUM_4 && data->selected_object)  // rotate y+
	{
		if (data->selected_object->type == PLANE || data->selected_object->type == CYLINDER)
		{
			rotate_object_y(data->selected_object, -0.1f);
			data->needs_update = true;
		}
	}
	else if (key == KEY_NUM_6 && data->selected_object)  // rotate y-
	{
		if (data->selected_object->type == PLANE || data->selected_object->type == CYLINDER)
		{
			rotate_object_y(data->selected_object, 0.1f);
			data->needs_update = true;
		}
	}
	// light translation
	else if (key == KEY_HOME)
		move_light_z(data, &data->scene->light, -data->move_speed);
	else if (key == KEY_END)
		move_light_z(data, &data->scene->light, data->move_speed);
	else if (key == KEY_DELETE)
		move_light_x(data, &data->scene->light, -data->move_speed);
	else if (key == KEY_PAGEDOWN)
		move_light_x(data, &data->scene->light, data->move_speed);
	else if (key == KEY_PAGEUP)
		move_light_y(data, &data->scene->light, data->move_speed);
	else if (key == KEY_INSERT)
		move_light_y(data, &data->scene->light, -data->move_speed);
	// object selection
	else if (key == KEY_PLUS)
		select_next_object(data);
	else if (key == KEY_MINUS)
		select_prev_object(data);

	if (data->selected_object)
	{
		if (key == KEY_I)  // forward
		{
			if (data->selected_object->type == SPHERE)
				move_sphere_z(data, data->selected_object, -data->move_speed);
			else if (data->selected_object->type == PLANE)
				move_plane_z(data, data->selected_object, -data->move_speed);
		}
		else if (key == KEY_K)  // backward
		{
			if (data->selected_object->type == SPHERE)
				move_sphere_z(data, data->selected_object, data->move_speed);
			else if (data->selected_object->type == PLANE)
				move_plane_z(data, data->selected_object, data->move_speed);
		}
		else if (key == KEY_J)  // left
		{
			if (data->selected_object->type == SPHERE)
				move_sphere_x(data, data->selected_object, -data->move_speed);
			else if (data->selected_object->type == PLANE)
				move_plane_x(data, data->selected_object, -data->move_speed);
		}
		else if (key == KEY_L)  // right
		{
			if (data->selected_object->type == SPHERE)
				move_sphere_x(data, data->selected_object, data->move_speed);
			else if (data->selected_object->type == PLANE)
				move_plane_x(data, data->selected_object, data->move_speed);
		}
		else if (key == KEY_U)  // up
		{
			if (data->selected_object->type == SPHERE)
				move_sphere_y(data, data->selected_object, data->move_speed);
			else if (data->selected_object->type == PLANE)
				move_plane_y(data, data->selected_object, data->move_speed);
		}
		else if (key == KEY_O)  // down
		{
			if (data->selected_object->type == SPHERE)
				move_sphere_y(data, data->selected_object, -data->move_speed);
			else if (data->selected_object->type == PLANE)
				move_plane_y(data, data->selected_object, -data->move_speed);
		}
		else if (key == KEY_LEFT_BRACKET)
		{
			if (data->selected_object->type == SPHERE)
			{
				data->selected_object->r -= 0.5f;
				if (data->selected_object->r < 0.5f)
					data->selected_object->r = 0.5f;
				data->needs_update = true;
			}
		}
		else if (key == KEY_RIGHT_BRACKET)
		{
			if (data->selected_object->type == SPHERE)
			{
				data->selected_object->r += 0.5f;
				if (data->selected_object->r < 0.5f)
					data->selected_object->r = 0.5f;
				data->needs_update = true;
			}
		}
	}
		
	if (data->needs_update) {
		init_viewport(data);
		put_pixels(data);
		mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
		data->needs_update = false;
	}
	return (EXIT_SUCCESS);
	
}

void select_next_object(t_data *data)
{
	if (!data->scene->objects)
		return;
	if (!data->selected_object)
		data->selected_object = data->scene->objects;
	else if (data->selected_object->next)
		data->selected_object = data->selected_object->next;
	else //wrap around to the start
		data->selected_object = data->scene->objects;

	printf("Selected object: type=%d at (%f, %f, %f)\n",
	data->selected_object->type,
	data->selected_object->center.x,
	data->selected_object->center.y,
	data->selected_object->center.z);
}

void select_prev_object(t_data *data)
{
	t_obj	*current;
	
	if (!data->scene->objects)
		return;
	// if nothing is selected or at the head, go to last
	if (!data->selected_object || data->selected_object == data->scene->objects)
	{
		// go to last
		current = data->scene->objects;
		while (current->next)
			current = current->next;
		data->selected_object = current;
	}
	else
	{
		current = data->scene->objects;
		while (current && current->next != data->selected_object)
			current = current->next;
		if (current)
			data->selected_object = current;
		else
			data->selected_object = NULL;
	}

	printf("Selected object: type=%d at (%f, %f, %f)\n",
	data->selected_object->type,
	data->selected_object->center.x,
	data->selected_object->center.y,
	data->selected_object->center.z);
	
}