/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:07:28 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/23 11:56:16 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	rgb_to_int(t_colour c)
{
	int	res;

	res = c.r << 16;
	res += c.g << 8;
	res += c.b;
	return (res);
}

// void	c_scale_inplace(t_colour *colour, float c)
// {
// 	colour->r = fmin(255, colour->r * c);
// 	colour->g = fmin(255, colour->g * c);
// 	colour->b = fmin(255, colour->b * c);
// }

t_colour	c_clamp(t_colour colour)
{
	if (colour.r > 255)
		colour.r = 255;
	else if (colour.r < 0)
		colour.r = 0;
	if (colour.g > 255)
		colour.g = 255;
	else if (colour.g < 0)
		colour.g = 0;
	if (colour.b > 255)
		colour.b = 255;
	else if (colour.b < 0)
		colour.b = 0;
	return (colour);
}

t_colour	c_add(t_colour a, t_colour b)
{
	t_colour	res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return (c_clamp(res));
}

t_colour	c_scale(t_colour colour, float c)
{
	t_colour	res;

	res.r = colour.r * c;
	res.g = colour.g * c;
	res.b = colour.b * c;
	return (c_clamp(res));
}

// t_colour	add_ambient(t_colour obj, t_colour a_light)
// {
// 	t_colour	res;

// 	res.r = obj.r * (1.0f - a_light.ratio) + a_light.r * a_light.ratio;
// 	res.g = obj.g * (1.0f - a_light.ratio) + a_light.g * a_light.ratio;
// 	res.b = obj.b * (1.0f - a_light.ratio) + a_light.b * a_light.ratio;
// 	return (res);
// }

void	add_ambient(t_colour *obj, t_colour a_light)
{
	obj->r = obj->r * (1.0f - a_light.ratio) + a_light.r * a_light.ratio;
	obj->g = obj->g * (1.0f - a_light.ratio) + a_light.g * a_light.ratio;
	obj->b = obj->b * (1.0f - a_light.ratio) + a_light.b * a_light.ratio;
}
