/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:00:55 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/07 01:23:13 by ykhattab         ###   ########.fr       */
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
	/* ------------------------------ */
	else if (key == KEY_PLUS)
		select_next_object(data);
	else if (key == KEY_MINUS)
		select_prev_object(data);

	if (data->selected_object)
	{
		if (key == KEY_I)  // forward
			move_sphere_z(data, data->selected_object, -data->move_speed);
		else if (key == KEY_K)  // backward
			move_sphere_z(data, data->selected_object, data->move_speed);
		else if (key == KEY_J)  // left
			move_sphere_x(data, data->selected_object, -data->move_speed);
		else if (key == KEY_L)  // right
			move_sphere_x(data, data->selected_object, data->move_speed);
		else if (key == KEY_U)  // up
			move_sphere_y(data, data->selected_object, data->move_speed);
		else if (key == KEY_O)  // down
			move_sphere_y(data, data->selected_object, -data->move_speed);
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