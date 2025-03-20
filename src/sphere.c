/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:10 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/20 13:56:46 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

float	hit_sphere(t_ray r, t_sphere *sp)
{
	float	d;
	float	a;
	float	b;
	float	c;
	t_vec3	oc;

	oc = v_subtract(sp->center, r.start);
	a = v_dot(r.dir, r.dir);
	b = -2.0 * v_dot(r.dir, oc);
	c = v_dot(oc, oc) - sp->r * sp->r;
	d = b * b - 4 * a * c;
	// printf("a=%f, b=%f, c=%f, d=%f\n", a, b, c, d);
	return (d);
}
