/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:00:55 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/10 09:25:15 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void key_object_rotation(int key, t_data *data)
{
	bool	rotation_applied;
	float	angle;

	rotation_applied = false;
	angle = 0.1f;
	if (key == KEY_NUM_8)
		rotation_applied = rotate_object_x(data->selected_object, angle);
	else if (key == KEY_NUM_2)   // rotate x-
        rotation_applied = rotate_object_x(data->selected_object, -angle);
    else if (key == KEY_NUM_4)   // rotate y+
        rotation_applied = rotate_object_y(data->selected_object, -angle);
    else if (key == KEY_NUM_6)   // rotate ay-
        rotation_applied = rotate_object_y(data->selected_object, angle);
	else if (key == KEY_NUM_7)
        rotation_applied = rotate_object_z(data->selected_object, -angle);
    else if (key == KEY_NUM_9)
        rotation_applied = rotate_object_z(data->selected_object, angle);
	if (rotation_applied)
        data->needs_update = true;
}

static void	key_objects(int key, t_data *data)
{
	if (key == KEY_I)  // forward
		move_obj(data, data->selected_object, -1.f, 'z');
	else if (key == KEY_K)  // backward
		move_obj(data, data->selected_object, 1.f, 'z');
	else if (key == KEY_J)  // left
		move_obj(data, data->selected_object, -1.f, 'x');
	else if (key == KEY_L)  // right
		move_obj(data, data->selected_object, 1.f, 'x');
	else if (key == KEY_U)  // up
		move_obj(data, data->selected_object, 1.f, 'y');
	else if (key == KEY_O)  // down
		move_obj(data, data->selected_object, -1.f, 'y');
	else if (key == KEY_LEFT_BRACKET)
		change_r_h(data, data->selected_object, -1.f, 'r');
	else if (key == KEY_RIGHT_BRACKET)
		change_r_h(data, data->selected_object, 1.f, 'r');
	else if (key == KEY_SEMICOLON)
        change_r_h(data, data->selected_object, -1.f, 'h');
    else if (key == KEY_APOSTROPHE)
        change_r_h(data, data->selected_object, 1.f, 'h');
	else
		key_object_rotation(key, data);
}



static void	keys_camera(int key, t_data *data)
{
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
}

static void	keys_light(int key, t_data *data)
{
	if (key == KEY_T)
		move_light(data, &data->scene->light, -1.f, 'z');
	else if (key == KEY_G)
		move_light(data, &data->scene->light, 1.f, 'z');
	else if (key == KEY_F)
		move_light(data, &data->scene->light, -1.f, 'x');
	else if (key == KEY_H)
		move_light(data, &data->scene->light, 1.f, 'x');
	else if (key == KEY_R)
		move_light(data, &data->scene->light, 1.f, 'y');
	else if (key == KEY_Y)
		move_light(data, &data->scene->light, -1.f, 'y');
}

int	key_hook(int key, t_data *data)
{
	if (key == KEY_ESC)
		clean_exit(data);
	keys_light(key, data);
	keys_camera(key, data);
	if (key == KEY_PLUS)
		select_next_object(data);
	else if (key == KEY_MINUS)
		select_prev_object(data);
	if (data->selected_object)
		key_objects(key, data); // this now handles all
	if (data->needs_update)
	{
		init_viewport(data);
		put_pixels(data);
		mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
		data->needs_update = false;
	}
	return (EXIT_SUCCESS);
}

static void	print_obj_info(t_obj *obj)
{
	char	*obj_names[3];

	obj_names[0] = "SPHERE";
	obj_names[1] = "PLANE";
	obj_names[2] = "CYLINDER";
	if (!obj)
	{
		printf("No object selected.\n");
		return ;
	}
	printf("Selected object: type=%s at (%.2f, %.2f, %.2f)\n",
		obj_names[obj->type],
		obj->center.x,
		obj->center.y,
		obj->center.z);
}

void	select_next_object(t_data *data)
{
	if (!data->scene->objects)
		return ;
	if (!data->selected_object)
		data->selected_object = data->scene->objects;
	else if (data->selected_object->next)
		data->selected_object = data->selected_object->next;
	else //wrap around to the start
		data->selected_object = data->scene->objects;
	print_obj_info(data->selected_object);
}

void	select_prev_object(t_data *data)
{
	t_obj	*current;

	if (!data->scene->objects)
		return ;
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
	print_obj_info(data->selected_object);
}
