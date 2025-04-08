/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:20:18 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/08 11:20:58 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_vec3	side_normal(t_ray r, t_obj *cy, float t)
{
	t_vec3	normal;
	t_vec3	cp;
	t_vec3	proj;

	cp = v_subtract(v_at(r, t), cy->center);
	proj = v_scale(cy->norm, v_dot(cp, cy->norm));
	normal = v_unit(v_subtract(cp, proj));
	return (normal);
}

static bool	within_height(t_obj *cy, t_ray r, float t)
{
	t_vec3	p;
	t_vec3	cp;
	float	proj;

	if (!isnan(t))
	{
		p = v_at(r, t);
		cp = v_subtract(p, cy->center);
		proj = v_dot(cp, cy->norm);
		if (fabs(proj) <= cy->h / 2)
			return (true);
	}
	return (false);
}

static bool	within_circle(t_hit hit, t_obj plane, float radius, t_ray r)
{
	t_vec3	p;
	t_vec3	v;
	t_vec3	projection;
	t_vec3	v_tangent;

	if (!isnan(hit.t) && hit.t > 0)
	{
		p = v_at(r, hit.t);
		v = v_subtract(p, plane.point);
		projection = v_scale(plane.norm, v_dot(v, plane.norm));
		v_tangent = v_subtract(v, projection);
		if (v_len(v_tangent) <= radius)
			return (true);
	}
	return (false);
}

static t_hit	min_top_bottom(t_ray r, t_obj *cy)
{
	t_obj	top;
	t_obj	bottom;
	t_hit	top_hit;
	t_hit	bottom_hit;
	t_hit	min;

	min.t = nanf("");
	bottom.type = PLANE;
	top.type = PLANE;
	bottom.norm = v_scale(cy->norm, -1.0f);
	top.norm = cy->norm;
	top.point = v_add(cy->center, v_scale(cy->norm, cy->h / 2));
	bottom.point = v_subtract(cy->center, v_scale(cy->norm, cy->h / 2));
	top_hit = hit_plane(r, &top);
	bottom_hit = hit_plane(r, &bottom);
	if (within_circle(top_hit, top, cy->r, r))
		min = top_hit;
	if ((isnan(min.t) || bottom_hit.t < min.t) && within_circle(bottom_hit,
			bottom, cy->r, r))
		min = bottom_hit;
	return (min);
}

t_hit	hit_cylinder(t_ray r, t_obj *cy)
{
	t_hit	hit;
	t_vec3	oc;
	float	d;
	float	a;
	float	b;

	hit.t = nanf("");
	oc = v_subtract(r.start, cy->center);
	a = v_dot(r.dir, r.dir) - powf(v_dot(r.dir, cy->norm), 2);
	b = 2.0 * (v_dot(r.dir, oc) - v_dot(r.dir, cy->norm) * v_dot(oc, cy->norm));
	d = b * b - 4 * a * (v_dot(oc, oc) - powf(v_dot(oc, cy->norm), 2)
			- powf(cy->r, 2));
	if (within_height(cy, r, solve_quadratic(d, a, b)))
	{
		hit.t = solve_quadratic(d, a, b);
		hit.normal = side_normal(r, cy, hit.t);
	}
	if (isnan(hit.t) || (!isnan(hit.t) && !isnan(min_top_bottom(r, cy).t)
			&& (hit.t >= min_top_bottom(r, cy).t)))
		return (min_top_bottom(r, cy));
	return (hit);
}
