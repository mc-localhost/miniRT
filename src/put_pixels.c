/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:07 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/23 12:12:37 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_ray	send_cam_ray(t_data *data, int x, int y)
{
	t_ray	ray;
	t_vec3	pixel_center;

	ray.start = data->scene->camera.view_point;
	pixel_center = data->pixel00_loc;
	v_add_inplace(&pixel_center, v_scale(data->pixel_delta_u, (float)x));
	v_add_inplace(&pixel_center, v_scale(data->pixel_delta_v, (float)y));
	ray.dir = v_subtract(pixel_center, ray.start);
	return (ray);
}

void	put_pixel_to_img(t_img *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int *)dst = colour;
}

static float	hit_object(t_ray ray, t_obj *curr)
{
	if (curr->type == SPHERE)
		return (hit_sphere(ray, curr));
	// else if (curr->type == PLANE)
	// 	return hit_plane(ray, curr);
	// else if (curr->type == CYLINDER)
	// 	return hit_cylinder(ray, curr);
	return (nanf(""));
}

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
		t = hit_object(shadow_ray, curr);
		if (!isnan(t) && t > 0.001f && t < light_distance)
			return (true);
		curr = curr->next;
	}
	return (false);
}

static t_colour	hit_objects(t_data *data, t_ray ray)
{
	t_hit	hit;
	t_hit	closest_hit;
	t_obj	*curr;

	closest_hit.t = INFINITY;
	closest_hit.colour = (t_colour){0, 0, 0, 0.f}; //background colour
	curr = data->scene->objects;
	while (curr)
	{
		hit.t = hit_object(ray, curr);
		if (!isnan(hit.t))
		{
			// move this inside hit function, hit function will return hit instance
			hit.normal = v_unit(v_subtract(v_at(ray, hit.t), curr->center)); // sphere has center, so only works for it rn
			if (v_dot(ray.dir, hit.normal) < 0)
				hit.front_face = true;
			else
			{
				hit.front_face = false;
				v_scale_inplace(&hit.normal, -1.f);
			}
			hit.colour = curr->colour;
			// hit.colour.r *= 0.5f * (hit.normal.x + 1);
			// hit.colour.g *= 0.5f * (hit.normal.y + 1);
			// hit.colour.b *= 0.5f * (hit.normal.z + 1);
			if (hit.t < closest_hit.t)
				closest_hit = hit;
		}
		curr = curr->next;
	}
	if (closest_hit.t != INFINITY)
	{
		t_vec3 light_dir = v_unit(v_subtract(data->scene->light.pos, v_at(ray, closest_hit.t)));
		float light_intensity = fmax(0.0f, v_dot(closest_hit.normal, light_dir)) * data->scene->light.colour.ratio;
		if (!in_shadow(data, v_at(ray, closest_hit.t), data->scene->light))
			closest_hit.colour = c_scale(closest_hit.colour, light_intensity);
		else
			closest_hit.colour = c_scale(closest_hit.colour, light_intensity * 0.2f);
		add_ambient(&closest_hit.colour, data->scene->a_light);
	}
	return (closest_hit.colour);
}

void	put_pixels(t_data *data)
{
	t_colour	colour;
	t_ray		ray;
	int			x;
	int			y;

	y = 0;
	while (y < data->h)
	// while (y < 10)
	{
		x = 0;
		while (x < data->w)
		// while (x < 2)
		{
			ray = send_cam_ray(data, x, y);
			colour = hit_objects(data, ray);
			put_pixel_to_img(&data->img, x, y, rgb_to_int(colour));
			x++;
		}
		y++;
	}
}
