/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 02:10:38 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/08 12:47:49 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// void move_light_x(t_data *data, t_light *light, float distance)
// {
//     t_vec3 movement = {distance, 0.0f, 0.0f};

//     v_add_inplace(&light->pos, movement);
//     data->needs_update = true;
// }

// void move_light_y(t_data *data, t_light *light, float distance)
// {
//     t_vec3 movement = {0.0f, distance, 0.0f};

//     v_add_inplace(&light->pos, movement);
//     data->needs_update = true;
// }

// void move_light_z(t_data *data, t_light *light, float distance)
// {
//     t_vec3 movement = {0.0f, 0.0f, distance};

//     v_add_inplace(&light->pos, movement);
//     data->needs_update = true;
// }

void	move_light(t_data *data, t_light *light, float coef, char dir)
{
	float	dist;
	t_vec3	movement;

    dist = coef * data->move_speed;
	if (dir == 'x')
		movement = (t_vec3){dist, 0.0f, 0.0f};
	else if (dir == 'y')
		movement = (t_vec3){0.0f, dist, 0.0f};
	else
		movement = (t_vec3){0.0f, 0.0f, dist};
	v_add_inplace(&light->pos, movement);
	data->needs_update = true;
}
