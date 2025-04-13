/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 05:07:44 by yousef            #+#    #+#             */
/*   Updated: 2025/04/13 12:25:23 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static	int	validate_parts(char **parts)
{
	if (!parts)
		return (error_message("Error\nMemory allocation failure"));
	if (!parts[0] || !*parts[0])
		return (free_and_error(parts, "Error\nMissing identifier"));
	return (0);
}

int	parse_line(char *line, t_scene *scene)
{
	int		result;
	char	**parts;

	if (!line || !*line)
		return (EXIT_SUCCESS);
	parts = ft_split(line, ' ');
	result = validate_parts(parts);
	if (result != EXIT_SUCCESS)
		return (result);
	if (ft_strcmp(parts[0], "A") == 0)
		result = parse_ambient(line, scene);
	else if (ft_strcmp(parts[0], "C") == 0)
		result = parse_camera(line, scene);
	else if (ft_strcmp(parts[0], "L") == 0)
		result = parse_light(line, scene);
	else if (ft_strcmp(parts[0], "sp") == 0)
		result = parse_obj(line, scene, SPHERE);
	else if (ft_strcmp(parts[0], "pl") == 0)
		result = parse_obj(line, scene, PLANE);
	else if (ft_strcmp(parts[0], "cy") == 0)
		result = parse_obj(line, scene, CYLINDER);
	else
		return (free_and_error(parts, "Error\nInvalid object identifier"));
	free_split(parts);
	return (result);
}

int	parse_camera(char *line, t_scene *scene)
{
	char	**s;
	t_vec3	norm_vector;

	s = validate_params(line, 4, "Error\nCamera line has wrong parameters");
	if (!s)
		return (EXIT_FAILURE);
	scene->camera.view_point = parse_vector(s[1]);
	norm_vector = parse_vector(s[2]);
	if (isnan(scene->camera.view_point.x) || isnan(norm_vector.x))
		return (free_and_error(s, "Error\nInvalid camera vector"));
	if (v_len(norm_vector) < 0.01f || !is_normalized(norm_vector))
		return (free_and_error(s,
				"Error\nCamera norm vector must be normalized"));
	scene->camera.norm = v_unit(norm_vector);
	if (!is_number(s[3]))
		return (free_and_error(s, "Error\nCamera FOV must be a number"));
	scene->camera.fov_deg = ft_atoi(s[3]);
	if (scene->camera.fov_deg < 0 || scene->camera.fov_deg > 180)
		return (free_and_error(s,
				"Error\nCamera FOV must be between 0 and 180."));
	scene->camera.fov_rad = scene->camera.fov_deg * (M_PI / 180.f);
	free_split(s);
	return (EXIT_SUCCESS);
}
