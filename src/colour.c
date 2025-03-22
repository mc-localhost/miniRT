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