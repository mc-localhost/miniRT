/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:13 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/11 19:42:11 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_obj	*create_object(t_type type, t_vec3 norm, float diameter, float h)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->norm = norm;
	obj->diameter = diameter;
	obj->r = diameter / 2.f;
	obj->h = h;
	obj->next = NULL;
	return (obj);
}

void	add_object(t_obj **list, t_obj *new_obj)
{
	t_obj	*temp;

	if (!*list)
	{
		*list = new_obj;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_obj;
}
