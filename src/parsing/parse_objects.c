/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:57:21 by yousef            #+#    #+#             */
/*   Updated: 2025/04/12 20:51:22 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

char	**validate_params(char *line, int param_count, char *err_msg)
{
	char	**s;
	int		i;
	char	*trimmed;
	char	*normalized;

	trimmed = ft_strtrim(line, " \t\n\r\f\v");
	if (!trimmed)
		return (NULL);
	normalized = normalize_whitespace(trimmed);
	free(trimmed);
	if (!normalized)
		return (NULL);
	s = ft_split(normalized, ' ');
	free(normalized);
	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (i != param_count)
	{
		free_split(s);
		return (error_return_null_char(err_msg));
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

static int	validate_vectors(char **s, t_type type, t_vec3 *center,
		t_vec3 *normal)
{
	*center = parse_vector(s[1]);
	if (isnan(center->x))
		return (error_message("Error\nInvalid center vector"));
	if (type == PLANE || type == CYLINDER)
	{
		*normal = parse_vector(s[2]);
		if (isnan(normal->x))
			return (error_message("Error\nInvalid normal/axis vector"));
		if (v_len(*normal) < 0.01f || !is_normalized(*normal))
			return (error_message("Error\nNormal/axis vector must be \
				normalized / cannot be zero"));
	}
	return (EXIT_SUCCESS);
}

t_obj	*parse_obj_params(char **s, t_type type)
{
	t_obj		*obj;
	t_vec3		center;
	t_vec3		normal;
	t_colour	colour;

	if (!s)
		return (error_return_null("Error\nNull input parameters"));
	obj = NULL;
	if (validate_vectors(s, type, &center, &normal) != EXIT_SUCCESS)
		return (NULL);
	colour = parse_obj_colour(s, type);
	if (!validate_colour(colour))
		return (error_return_null("Error\nInvalid colour specification"));
	if (type == SPHERE)
		obj = create_sphere(s);
	else if (type == PLANE)
		obj = create_plane(s);
	else if (type == CYLINDER)
		obj = create_cylinder(s);
	if (!obj)
		return (error_return_null("Error\nFailed to create object"));
	obj->center = center;
	obj->point = center;
	obj->colour = colour;
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
		return (EXIT_FAILURE);
	}
	add_object(&scene->objects, new_obj);
	free_split(s);
	return (EXIT_SUCCESS);
}
