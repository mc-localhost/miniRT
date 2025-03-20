/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:07 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/20 13:56:40 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_ray	send_cam_ray(t_data *data, int x, int y)
{
	t_ray	ray;
	t_vec3	pixel_center;

	ray.start = data->scene->camera.view_point; //(t_vec3){0.f, 0.f, 0.f}; at the moment
	//change later as in https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera
	pixel_center = data->pixel00_loc;
	v_add_inplace(&pixel_center, v_scale(data->pixel_delta_u, (float)x));
	v_add_inplace(&pixel_center, v_scale(data->pixel_delta_v, (float)y));
	// printf("pixel_center ={%f, %f, %f}\n",pixel_center.x, pixel_center.y, pixel_center.z);
	ray.dir = v_subtract(pixel_center, ray.start);
	return (ray);
}

int	rgb_to_int(t_colour c)
{
	int	res;

	res = c.r << 16;
	res += c.g << 8;
	res += c.b;
	return (res);
}

void	put_pixel_to_img(t_img *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int *)dst = colour;
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
			// printf("ray dir ={%f, %f, %f}\n", ray.dir.x, ray.dir.y, ray.dir.z);
			if (hit_sphere(ray, data->scene->spheres[0]) >= 0)
			{
				colour = (t_colour){255, 0, 0, 1.f};
				// printf("hit sphere at x=%d, y=%d with ray dir ={%f, %f, %f}\n", x, y, ray.dir.x, ray.dir.y, ray.dir.z);
			}
			else
			{
				colour = (t_colour){0, 0, 0, 0.f};
				// printf("DID NOT hit sphere at x=%d, y=%d\n", x, y);
			}
			put_pixel_to_img(&data->img, x, y, rgb_to_int(colour));
			x++;
		}
		y++;
	}
}
