/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:20:15 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/12 17:54:44 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_hit	hit_plane(t_ray r, t_obj *pl)
{
	float	dot;
	t_hit	hit;

	dot = v_dot(r.dir, pl->norm);
	if (fabs(dot) > 0)
		hit.t = v_dot(v_subtract(pl->point, r.start), pl->norm) / dot;
	else
		hit.t = nanf("");
	hit.normal = pl->norm;
	return (hit);
}
