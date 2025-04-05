/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 05:07:44 by yousef            #+#    #+#             */
/*   Updated: 2025/04/05 21:39:14 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"


int parse_line(char *line, t_scene *scene)
{
	int result;

	result = EXIT_SUCCESS;
	if (line[0] == 'A')
		result = parse_ambient(line, scene);
	else if (line[0] == 'C')
		result = parse_camera(line, scene);
	else if (line[0] == 'L')
		result = parse_light(line, scene);
	else if (ft_strncmp(line, "sp", 2) == 0)
		result = parse_sphere(line, scene);
	else if (ft_strncmp(line, "pl", 2) == 0)
		result = parse_plane(line, scene);
	else if (ft_strncmp(line, "cy", 2) == 0)
		result = parse_cylinder(line, scene);
	else
		return(error_message("Error: Invalid object or malformed line"));
	return (result);
}

int parse_camera(char *line, t_scene *scene)
{
	char	**s;
	
	s = ft_split(line, ' ');
	if (!s || !s[1] || !s[2] || !s[3])
	{
		free_split(s);
		return (error_message("Error: Camera line missing parameters"));
	}
	scene->camera.view_point = parse_vector(s[1]);
	scene->camera.norm = v_unit(parse_vector(s[2]));
	if (v_len(scene->camera.norm) < 0.01f)
	{
		free_split(s);
		return (error_message("Error: Camera direction vector cannot be zero."));
	}
	scene->camera.fov_deg = ft_atoi(s[3]);
	if (scene->camera.fov_deg < 0 || scene->camera.fov_deg > 180)
	{
		free_split(s);
		return (error_message("Error: Camera FOV must be between 0 and 180 degrees."));
	}
	scene->camera.fov_rad = scene->camera.fov_deg * (M_PI / 180.f);
	free_split(s);
	return (EXIT_SUCCESS);
}
