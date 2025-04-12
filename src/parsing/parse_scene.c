/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 05:07:44 by yousef            #+#    #+#             */
/*   Updated: 2025/04/12 01:28:29 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	parse_line(char *line, t_scene *scene)
{
	int		result;
	char	**parts;

	if (!line || !*line)
		return (EXIT_SUCCESS);
	parts = ft_split(line, ' ');
	if (!parts)
		return (error_message("Error\nMemory allocation failure"));
	if (!parts[0] || !*parts[0])
		return (free_and_error(parts, "Error\nMissing identifier"));
	result = EXIT_SUCCESS;
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
	t_vec3  norm_vector;

	s = ft_split(line, ' ');
	if (!s || !s[1] || !s[2] || !s[3])
		return (free_and_error(s, "Error\nCamera line missing parameters"));
	scene->camera.view_point = parse_vector(s[1]);
	norm_vector = parse_vector(s[2]);
	if (v_len(norm_vector) < 0.01f || !is_normalized(norm_vector))
    return (free_and_error(s, 
		"Error\nCamera norm vector must be normalized / cannot be zero"));
    scene->camera.norm = v_unit(norm_vector);
    scene->camera.fov_deg = ft_atoi(s[3]);
    if (scene->camera.fov_deg < 0 || scene->camera.fov_deg > 180)
    	return (free_and_error(s, 
		"Error\nCamera FOV must be between 0 and 180."));
    scene->camera.fov_rad = scene->camera.fov_deg * (M_PI / 180.f);
    free_split(s);
    return (EXIT_SUCCESS);
}
