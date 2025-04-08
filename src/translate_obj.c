/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:12:00 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/08 13:19:54 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	move_obj(t_data *data, t_obj *obj, float coef, char dir)
{
	float	dist;
	t_vec3	movement;

	dist = coef * data->move_speed;
	if (dir == 'x')
		movement = (t_vec3){dist, 0.0f, 0.0f};
	else if (dir == 'y')
		movement = (t_vec3){0.0f, dist, 0.0f};
	else if (dir == 'z')
		movement = (t_vec3){0.0f, 0.0f, dist};
	if (obj->type == SPHERE || obj->type == CYLINDER)
		v_add_inplace(&obj->center, movement);
	else if (obj->type == PLANE)
		v_add_inplace(&obj->point, movement);
	data->needs_update = true;
}
