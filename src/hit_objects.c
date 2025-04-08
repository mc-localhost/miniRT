/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:07 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/08 14:45:55 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static bool	in_shadow(t_data *data, t_vec3 point, t_light light)
{
	t_ray	shadow_ray;
	t_obj	*curr;
	float	light_distance;
	float	t;

	shadow_ray.start = point;
	shadow_ray.dir = v_unit(v_subtract(light.pos, point));
	light_distance = v_len(v_subtract(light.pos, point));
	curr = data->scene->objects;
	while (curr)
	{
		t = hit_object(shadow_ray, curr).t;
		if (!isnan(t) && t > 0.001f && t < light_distance)
			return (true);
		curr = curr->next;
	}
	return (false);
}

/* black colour is set by default for closest_hit*/

static t_hit	find_closest_hit(t_data *data, t_ray ray)
{
	t_hit	hit;
	t_hit	closest_hit;
	t_obj	*curr;

	closest_hit.t = INFINITY;
	closest_hit.colour = (t_colour){0, 0, 0, 0.f};
	curr = data->scene->objects;
	while (curr)
	{
		hit = hit_object(ray, curr);
		if (!isnan(hit.t) && hit.t >= 1e-6)
		{
			if (hit.t < closest_hit.t)
				closest_hit = hit;
		}
		curr = curr->next;
	}
	return (closest_hit);
}

t_hit	hit_object(t_ray ray, t_obj *curr)
{
	t_hit	hit;

	if (curr->type == SPHERE)
		hit = hit_sphere(ray, curr);
	else if (curr->type == PLANE)
		hit = hit_plane(ray, curr);
	else if (curr->type == CYLINDER)
		hit = hit_cylinder(ray, curr);
	hit.front_face = v_dot(ray.dir, hit.normal) < 0;
	if (!hit.front_face)
		v_scale_inplace(&hit.normal, -1.f);
	hit.colour = curr->colour;
	return (hit);
}

t_colour	hit_objects(t_data *data, t_ray ray)
{
	t_hit	closest_hit;
	t_vec3	light_dir;
	float	light_intensity;

	closest_hit = find_closest_hit(data, ray);
	if (closest_hit.t != INFINITY)
	{
		light_dir = v_unit(v_subtract(data->scene->light.pos, v_at(ray,
						closest_hit.t)));
		light_intensity = fmax(0.0f, v_dot(closest_hit.normal, light_dir))
			* data->scene->light.colour.ratio;
		add_ambient(&closest_hit.colour, data->scene->a_light);
		if (!in_shadow(data, v_at(ray, closest_hit.t), data->scene->light))
			closest_hit.colour = c_scale(closest_hit.colour, light_intensity);
		else
			closest_hit.colour = c_scale(closest_hit.colour, light_intensity
					* 0.2f);
	}
	return (closest_hit.colour);
}
