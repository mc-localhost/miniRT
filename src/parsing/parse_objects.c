/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:57:21 by yousef            #+#    #+#             */
/*   Updated: 2025/04/08 15:54:52 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

char	**validate_params(char *line, int param_count, char *err_msg)
{
	char	**s;
	int		i;

	s = ft_split(line, ' ');
	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (i < param_count) //and what if there are 100 params?
	{
		free_split(s);
		error_message(err_msg);
		return (NULL);
	}
	return (s);
}

static t_colour	parse_obj_colour(char **s, t_type type)
{
	t_colour	colour;

	colour = INVALID_COL;
	if (type == SPHERE)
		colour = parse_colour(s[3]);
	else if (type == PLANE)
		colour = parse_colour(s[3]);
	else if (type == CYLINDER)
		colour = parse_colour(s[5]);
	return (colour);
}

t_obj	*parse_obj_params(char **s, t_type type)
{
	t_obj		*obj;
	t_vec3		center;
	t_colour	colour;

	obj = NULL;
	center = parse_vector(s[1]);
	if (isnan(center.x))
		return (NULL);
	colour = parse_obj_colour(s, type);
	if (!validate_colour(colour))
		return (NULL);
	//obj shoulod only be created if all vectors and floats and colours are good
	//ft_atofs unchecked
	//parse_vector unchecked
	if (type == SPHERE)
		obj = create_object(SPHERE, (t_vec3){0, 0, 0}, ft_atof(s[2]), 0);
	else if (type == PLANE)
		obj = create_object(PLANE, v_unit(parse_vector(s[2])), 0, 0);
	else if (type == CYLINDER)
		obj = create_object(CYLINDER, v_unit(parse_vector(s[2])), ft_atof(s[3]), ft_atof(s[4]));
	if (obj)
	{
		obj->center = center;
		obj->point = center;
		obj->colour = colour;
	}
	return (obj);
}

int	parse_obj(char *line, t_scene *scene, t_type type)
{
	char	**s;
	t_obj	*new_obj;

	if (type == SPHERE)
		s = validate_params(line, 4, "Error\nSphere line wrong parameters");
	else if (type == PLANE)
		s = validate_params(line, 4, "Error\nPlane has wrong parameters");
	else if (type == CYLINDER)
		s = validate_params(line, 6, "Error\nCylinder has wrong parameters");
	else
		return (EXIT_FAILURE);
	if (!s)
		return (EXIT_FAILURE);
	new_obj = parse_obj_params(s, type);
	if (!new_obj)
	{
		free_split(s);
		return (error_message("Error\nFailed to create object"));
	}
	add_object(&scene->objects, new_obj);
	free_split(s);
	return (EXIT_SUCCESS);
}
