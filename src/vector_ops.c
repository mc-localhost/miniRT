/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:15 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/21 09:58:47 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vec3	v_add(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	res;

	res = vec;
	res.x += vec2.x;
	res.y += vec2.y;
	res.z += vec2.z;
	return (res);
}

t_vec3	v_subtract(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	res;

	res = vec;
	res.x -= vec2.x;
	res.y -= vec2.y;
	res.z -= vec2.z;
	return (res);
}

t_vec3	v_scale(t_vec3 vec, float c)
{
	t_vec3	res;

	res.x = vec.x * c;
	res.y = vec.y * c;
	res.z = vec.z * c;
	return (res);
}

float	v_len(t_vec3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	v_unit(t_vec3 vec)
{
	return (v_scale(vec, 1.f / v_len(vec)));
}

t_vec3	v_at(t_ray ray, float t)
{
	return (v_add(ray.start, v_scale(ray.dir, t)));
}

float	v_dot(t_vec3 vec, t_vec3 vec2)
{
	float	res;

	res = vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z;
	return (res);
}

t_vec3	v_cross(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	res;

	res.x = vec.y * vec2.z - vec.z * vec2.y;
	res.y = vec.z * vec2.x - vec.x * vec2.z;
	res.z = vec.x * vec2.y - vec.y * vec2.x;
	return (res);
}
