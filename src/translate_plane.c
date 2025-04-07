/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 02:10:38 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/07 02:50:45 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void move_plane_x(t_data *data, t_obj *plane, float distance)
{
    t_vec3 movement = {distance, 0.0f, 0.0f};
    
    v_add_inplace(&plane->point, movement);
    data->needs_update = true;
}

void move_plane_y(t_data *data, t_obj *plane, float distance)
{
    t_vec3 movement = {0.0f, distance, 0.0f};
    
    v_add_inplace(&plane->point, movement);
    data->needs_update = true;
}

void move_plane_z(t_data *data, t_obj *plane, float distance)
{
    t_vec3 movement = {0.0f, 0.0f, distance};
    
    v_add_inplace(&plane->point, movement);
    data->needs_update = true;
}
