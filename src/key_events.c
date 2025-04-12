/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:00:55 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/12 17:14:07 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	key_object_rotation(int key, t_data *data)
{
	bool	rotation_applied;
	float	angle;

	rotation_applied = false;
	angle = 0.1f;
	if (key == KEY_NUM_8)
		rotation_applied = rotate_object_x(data->selected_object, angle);
	else if (key == KEY_NUM_2)
		rotation_applied = rotate_object_x(data->selected_object, -angle);
	else if (key == KEY_NUM_4)
		rotation_applied = rotate_object_y(data->selected_object, -angle);
	else if (key == KEY_NUM_6)
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
	if (key == KEY_I)
		move_obj(data, data->selected_object, -1.f, 'z');
	else if (key == KEY_K)
		move_obj(data, data->selected_object, 1.f, 'z');
	else if (key == KEY_J)
		move_obj(data, data->selected_object, -1.f, 'x');
	else if (key == KEY_L)
		move_obj(data, data->selected_object, 1.f, 'x');
	else if (key == KEY_U)
		move_obj(data, data->selected_object, 1.f, 'y');
	else if (key == KEY_O)
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
	if (key == KEY_W)
		move_camera_forward(data, data->move_speed);
	else if (key == KEY_S)
		move_camera_forward(data, -data->move_speed);
	else if (key == KEY_A)
		move_camera_sideways(data, -data->move_speed);
	else if (key == KEY_D)
		move_camera_sideways(data, data->move_speed);
	else if (key == KEY_Q)
		move_camera_vertical(data, data->move_speed);
	else if (key == KEY_E)
		move_camera_vertical(data, -data->move_speed);
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
		key_objects(key, data);
	if (data->needs_update)
	{
		init_viewport(data);
		put_pixels(data);
		mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
		data->needs_update = false;
	}
	return (EXIT_SUCCESS);
}
