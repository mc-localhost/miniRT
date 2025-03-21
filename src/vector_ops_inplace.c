/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops_inplace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:15 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/21 09:58:36 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	v_add_inplace(t_vec3 *vec, t_vec3 vec2)
{
	vec->x += vec2.x;
	vec->y += vec2.y;
	vec->z += vec2.z;
}

void	v_subtract_inplace(t_vec3 *vec, t_vec3 vec2)
{
	vec->x -= vec2.x;
	vec->y -= vec2.y;
	vec->z -= vec2.z;
}

void	v_scale_inplace(t_vec3 *vec, float c)
{
	vec->x *= c;
	vec->y *= c;
	vec->z *= c;
}
