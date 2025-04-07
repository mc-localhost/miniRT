/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:12:00 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/06 02:23:21 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	move_sphere_x(t_data *data, t_obj *sphere, float distance)
{
	t_vec3 movement = {distance, 0.0f, 0.0f};
	
	v_add_inplace(&sphere->center, movement);
	data->needs_update = true;
}

void	move_sphere_y(t_data *data, t_obj *sphere, float distance)
{
	t_vec3 movement = {0.0f, distance, 0.0f};
	
	v_add_inplace(&sphere->center, movement);
	data->needs_update = true;
}

void move_sphere_z(t_data *data, t_obj *sphere, float distance)
{
    t_vec3 movement = {0.0f, 0.0f, distance};
    
    v_add_inplace(&sphere->center, movement);
    data->needs_update = true;
}
