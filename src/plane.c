/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:20:15 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/07 15:19:27 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_hit	hit_plane(t_ray r, t_obj *pl)
{
	float	dot;
	t_hit	hit;

	dot = v_dot(r.dir, pl->norm); //pl->norm should be normalised - check when parsing and apply v_unit if not
	if (fabs(dot) > 0) //plane norm and ray are not parallel, 1e-5 to account for floating point precision, otherwise should be 0
		hit.t = v_dot(v_subtract(pl->point, r.start), pl->norm) / dot;
	else
		hit.t = nanf("");
	hit.normal = pl->norm;
	return (hit);
}
