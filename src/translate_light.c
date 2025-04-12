/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 02:10:38 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/12 17:57:38 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

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
