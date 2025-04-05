/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:57:21 by yousef            #+#    #+#             */
/*   Updated: 2025/04/05 21:49:38 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static char	**validate_params(char *line, int param_count, char *err_msg)
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
		ft_putstr_stderr(err_msg);
		free_split(s);
		return (NULL);
	}
	return (s);
}

static t_obj	*parse_obj_params(char **s, t_type type) // review the error handling here after the changed parent function
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
	if (!obj)
		ft_putstr_stderr("Error: Failed to create object");
	return (obj);
}

int	parse_sphere(char *line, t_scene *scene)
{
	char	**s;
	t_obj	*new_obj;

	s = validate_params(line, 4, "Error: Sphere line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	new_obj = parse_obj_params(s, SPHERE);
	if (!new_obj)
	{
		free_split(s);
		return (EXIT_FAILURE);
	}
	add_object(&scene->objects, new_obj);
	free_split(s);
	return (EXIT_SUCCESS);
}

int	parse_plane(char *line, t_scene *scene)
{
	char	**s;
	t_obj	*new_obj;

	s = validate_params(line, 4, "Error: Plane line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	new_obj = parse_obj_params(s, PLANE);
	if (!new_obj)
	{
		free_split(s);
		return (EXIT_FAILURE);
	}
	add_object(&scene->objects, new_obj);
	free_split(s);
	return (EXIT_SUCCESS);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	char	**s;
	t_obj	*new_obj;

	s = validate_params(line, 6, "Error: Cylinder line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	new_obj = parse_obj_params(s, CYLINDER);
	if (!new_obj)
	{
		free_split(s);
		return (EXIT_FAILURE);
	}
	add_object(&scene->objects, new_obj);
	free_split(s);
	return (EXIT_SUCCESS);
}

int	parse_light(char *line, t_scene *scene)
{
	char	**s;
	
	s = validate_params(line, 4, "Error: Light line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	scene->light.pos = parse_vector(s[1]);
	// printf("output of ratio after atof: %f", scene->light.colour.ratio);
	if (!is_valid_ratio(ft_atof(s[2])))
	{
		free_split(s);
		return (error_message("Error: Invalid light ratio"));
	}
	scene->light.colour = parse_colour(s[3]);
	if (!validate_colour(scene->light.colour))
	{
		free_split(s);
		return (error_message("Error: Invalid colour in light"));
	}
	scene->light.colour.ratio = ft_atof(s[2]);
	free_split(s);
	return (EXIT_SUCCESS);
}

int	parse_ambient(char *line, t_scene *scene)
{
	char	**s;
	float	ratio;

	s = validate_params(line, 3, "Error: Ambient line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	ratio = ft_atof(s[1]);
	if (!is_valid_ratio(ratio))
	{
		free_split(s);
		return (error_message("Error: Invalid ambient light ratio"));
	}
	scene->a_light = parse_colour(s[2]);
	scene->a_light.ratio = ratio;
	if (!validate_colour(scene->a_light))
	{
		free_split(s);
		return (error_message("Error: Invalid colour in ambient light"));
	}
	free_split(s);
	return (EXIT_SUCCESS);
}
