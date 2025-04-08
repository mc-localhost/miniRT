/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:57:21 by yousef            #+#    #+#             */
/*   Updated: 2025/04/08 15:03:02 by vvasiuko         ###   ########.fr       */
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
	if (i < param_count)
	{
		free_split(s);
		error_message(err_msg);
		return (NULL);
	}
	return (s);
}

t_obj	*parse_obj_params(char **s, t_type type)
{
	t_obj	*obj;

	if (type == SPHERE)
	{
		obj = create_object(SPHERE, parse_vector(s[1]), parse_colour(s[3]),
				(t_vec3){0, 0, 0}, ft_atof(s[2]), 0);
	}
	else if (type == PLANE)
	{
		obj = create_object(PLANE, parse_vector(s[1]), parse_colour(s[3]),
				v_unit(parse_vector(s[2])), 0, 0);
	}
	else if (type == CYLINDER)
	{
		obj = create_object(CYLINDER, parse_vector(s[1]), parse_colour(s[5]),
				v_unit(parse_vector(s[2])), ft_atof(s[3]), ft_atof(s[4]));
	}
	else
		obj = NULL;
	return (obj);
}

int	parse_sphere(char *line, t_scene *scene)
{
	char	**s;
	t_obj	*new_obj;

	s = validate_params(line, 4, "Error\nSphere line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	new_obj = parse_obj_params(s, SPHERE);
	if (!new_obj)
	{
		free_split(s);
		return (error_message("Error\nFailed to create object"));
	}
	add_object(&scene->objects, new_obj);
	free_split(s);
	return (EXIT_SUCCESS);
}

int	parse_plane(char *line, t_scene *scene)
{
	char	**s;
	t_obj	*new_obj;

	s = validate_params(line, 4, "Error\nPlane line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	new_obj = parse_obj_params(s, PLANE);
	if (!new_obj)
	{
		free_split(s);
		return (error_message("Error\nFailed to create object"));
	}
	add_object(&scene->objects, new_obj);
	free_split(s);
	return (EXIT_SUCCESS);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	char	**s;
	t_obj	*new_obj;

	s = validate_params(line, 6, "Error\nCylinder line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	new_obj = parse_obj_params(s, CYLINDER);
	if (!new_obj)
	{
		free_split(s);
		return (error_message("Error\nFailed to create object"));
	}
	add_object(&scene->objects, new_obj);
	free_split(s);
	return (EXIT_SUCCESS);
}
