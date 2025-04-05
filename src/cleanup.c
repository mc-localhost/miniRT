/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:42:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/05 22:15:47 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

// void	free_scene(t_scene *scene) // maybe switch to garbage collector later
// {
// 	int	i;

// 	i = 0;
// 	if (scene->num_sp > 0)
// 	{
// 		while (i < scene->num_sp)
// 		{
// 			free(scene->spheres[i]);
// 			i++;
// 		}
// 		free(scene->spheres);
// 	}
// 	i = 0;
// 	if (scene->num_pl > 0)
// 	{
// 		while (i < scene->num_pl)
// 		{
// 			free(scene->planes[i]);
// 			i++;
// 		}
// 		free(scene->planes);
// 	}
// 	i = 0;
// 	if (scene->num_cy > 0)
// 	{
// 		while (i < scene->num_cy)
// 		{
// 			free(scene->cylinders[i]);
// 			i++;
// 		}
// 		free(scene->cylinders);
// 	}
// 	free(scene);
// }

void	free_scene(t_scene *scene) // maybe switch to garbage collector later
{
	t_obj	*current;
	t_obj	*next;

	current = scene->objects;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(scene);
}

int	clean_exit(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
		free(data->mlx);
	// + free everything else before exiting
	if (data->scene)
		free_scene(data->scene);
	exit(0);
}


int	key_hook(int key, t_data *data)
{
	if (key == 53)
		clean_exit(data);
	
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

	if (data->needs_update) {
		init_viewport(data);
		put_pixels(data);
		mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
		data->needs_update = false;
	}
	return (EXIT_SUCCESS);
	
}
