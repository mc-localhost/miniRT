/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_r_h.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 01:12:00 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/08 13:09:23 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	change_r_h(t_data *data, t_obj *obj, float coef, char r_h)
{
	if (obj->type == SPHERE || obj->type == CYLINDER)
	{
		if (r_h == 'r')
		{
			obj->r += coef * 0.5f;
			if (obj->r < 0.5f)
				obj->r = 0.5f;
		}
		else
		{
			obj->h += coef * 0.5f;
			if (obj->h < 0.5f)
				obj->h = 0.5f;
		}
		data->needs_update = true;
	}
}
