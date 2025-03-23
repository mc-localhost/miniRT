/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:42:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/23 11:07:50 by vvasiuko         ###   ########.fr       */
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

static void	free_scene(t_scene *scene) // maybe switch to garbage collector later
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

/* 53 = ESC */

int	key_hook(int k, t_data *data)
{
	if (k == 53)
		clean_exit(data);
	return (EXIT_SUCCESS);
}
