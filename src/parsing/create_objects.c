/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:50:06 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/12 20:53:42 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_obj	*create_sphere(char **s)
{
	double	value;
	t_obj	*obj;

	if (!is_valid_float(s[2]))
		return (error_return_null("Error\nInvalid format for sphere radius"));
	value = ft_atof(s[2]);
	if (value <= 0.0)
		return (error_return_null("Error\nSphere radius must be positive"));
	obj = create_object(SPHERE, (t_vec3){0, 0, 0}, value, 0);
	return (obj);
}

t_obj	*create_plane(char **s)
{
	t_vec3	normal;

	normal = parse_vector(s[2]);
	return (create_object(PLANE, v_unit(normal), 0, 0));
}

t_obj	*create_cylinder(char **s)
{
	double	radius;
	double	height;
	t_obj	*obj;
	t_vec3	normal;

	normal = parse_vector(s[2]);
	if (!is_valid_float(s[3]))
		return (error_return_null("Error\nInvalid format for cylinder radius"));
	radius = ft_atof(s[3]);
	if (radius <= 0.0)
		return (error_return_null("Error\nCylinder radius must be positive"));
	if (!is_valid_float(s[4]))
		return (error_return_null("Error\nInvalid format for cylinder height"));
	height = ft_atof(s[4]);
	if (height <= 0.0)
		return (error_return_null("Error\nCylinder height must be positive"));
	obj = create_object(CYLINDER, v_unit(normal), radius, 0);
	if (obj)
		obj->h = height;
	return (obj);
}
