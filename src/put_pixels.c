#include "../include/minirt.h"

t_ray send_cam_ray(t_data *data, int pix_c, int pix_r)
{
	t_vec3	viewport_upper_left;
	t_vec3	half_viewport_u;
	t_vec3	half_viewport_v;
	t_ray ray;

	// ray.start = data->scene->camera.view_point;
	//change later as in https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera
	ray.start = (t_vec3){0.f, 0.f, 0.f};
	ray.dir = data->scene->camera.norm.z;
	viewport_upper_left = data->scene->camera.view_point;
	half_viewport_u = data->viewport_u;
	v_scale(&half_viewport_u, 0.5f);
	half_viewport_v = data->viewport_v;
	v_scale(&half_viewport_v, 0.5f);
	v_subtract(&viewport_upper_left, (t_vec3){0, 0, data->focal_length});
	v_subtract(&viewport_upper_left, half_viewport_u);
	v_subtract(&viewport_upper_left, half_viewport_v);
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
	int		x;
	int		y;
	t_ray	ray;
	t_colour colour;

	y = 0;
	while (y < data->h)
	{
		x = 0;
		while (x < data->w)
		{
			ray = send_cam_ray(x, y);
			if (hit_sphere(ray, data->scene->spheres[0]) >= 0)
			{
				colour = (t_colour){255, 0, 0, 1.f};
			}
			put_pixel_to_img(&data->img, x, y, rgb_to_int(colour));
			x++;
		}
		y++;
	}
}
