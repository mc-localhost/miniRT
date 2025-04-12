/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 06:02:24 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/12 17:56:54 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

//same equation as the camera yaw rotation, but with different axes
bool	rotate_object_x(t_obj *obj, float angle)
{
	float	y;
	float	z;

	if (obj->type != PLANE && obj->type != CYLINDER)
		return (false);
	y = obj->norm.y;
	z = obj->norm.z;
	obj->norm.y = y * cosf(angle) - z * sinf(angle);
	obj->norm.z = y * sinf(angle) + z * cosf(angle);
	obj->norm = v_unit(obj->norm);
	printf("Object normal after X rotation: (%f, %f, %f)\n",
		obj->norm.x,
		obj->norm.y,
		obj->norm.z);
	return (true);
}

bool	rotate_object_y(t_obj *obj, float angle)
{
	float	x;
	float	z;

	if (obj->type != PLANE && obj->type != CYLINDER)
		return (false);
	x = obj->norm.x;
	z = obj->norm.z;
	obj->norm.x = x * cosf(angle) + z * sinf(angle);
	obj->norm.z = -x * sinf(angle) + z * cosf(angle);
	obj->norm = v_unit(obj->norm);
	printf("Object normal after Y rotation: (%f, %f, %f)\n",
		obj->norm.x,
		obj->norm.y,
		obj->norm.z);
	return (true);
}

bool	rotate_object_z(t_obj *obj, float angle)
{
	float	x;
	float	y;

	if (obj->type != PLANE && obj->type != CYLINDER)
		return (false);
	x = obj->norm.x;
	y = obj->norm.y;
	obj->norm.x = x * cosf(angle) - y * sinf(angle);
	obj->norm.y = x * sinf(angle) + y * cosf(angle);
	obj->norm = v_unit(obj->norm);
	printf("Object normal after Z rotation: (%f, %f, %f)\n",
		obj->norm.x,
		obj->norm.y,
		obj->norm.z);
	return (true);
}
