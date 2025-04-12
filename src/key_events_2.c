/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:14:38 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/12 17:16:36 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	print_obj_info(t_obj *obj)
{
	char	*obj_names[3];

	obj_names[0] = "SPHERE";
	obj_names[1] = "PLANE";
	obj_names[2] = "CYLINDER";
	if (!obj)
	{
		printf("No object selected.\n");
		return ;
	}
	printf("Selected object: type=%s at (%.2f, %.2f, %.2f)\n",
		obj_names[obj->type],
		obj->center.x,
		obj->center.y,
		obj->center.z);
}

void	select_next_object(t_data *data)
{
	if (!data->scene->objects)
		return ;
	if (!data->selected_object)
		data->selected_object = data->scene->objects;
	else if (data->selected_object->next)
		data->selected_object = data->selected_object->next;
	else
		data->selected_object = data->scene->objects;
	print_obj_info(data->selected_object);
}

void	select_prev_object(t_data *data)
{
	t_obj	*current;

	if (!data->scene->objects)
		return ;
	if (!data->selected_object || data->selected_object == data->scene->objects)
	{
		current = data->scene->objects;
		while (current->next)
			current = current->next;
		data->selected_object = current;
	}
	else
	{
		current = data->scene->objects;
		while (current && current->next != data->selected_object)
			current = current->next;
		if (current)
			data->selected_object = current;
		else
			data->selected_object = NULL;
	}
	print_obj_info(data->selected_object);
}
