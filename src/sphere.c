/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:10 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/23 15:13:40 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_hit	hit_sphere(t_ray r, t_obj *sp)
{
	t_hit	hit;
	float	d;
	float	a;
	float	b;
	t_vec3	oc;

	oc = v_subtract(sp->center, r.start);
	a = v_dot(r.dir, r.dir);
	b = -2.0 * v_dot(r.dir, oc);
	d = b * b - 4 * a * (v_dot(oc, oc) - sp->r * sp->r);
	hit.t = solve_quadratic(d, a, b);
	hit.normal = v_unit(v_subtract(v_at(r, hit.t), sp->center));
	return (hit);
}

float	solve_quadratic(float d, float a, float b)
{
	float	x1;
	float	x2;

	if (d < 0.0f)
		return (nanf(""));
	x1 = (-b + sqrtf(d)) / (2.f * a);
	x2 = (-b - sqrtf(d)) / (2.f * a);
	if (x2 > 0)
		return (x2);
	if (x1 > 0)
		return (x1);
	return (nanf(""));
}
