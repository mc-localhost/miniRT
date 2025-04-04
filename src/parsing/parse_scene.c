/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 05:07:44 by yousef            #+#    #+#             */
/*   Updated: 2025/04/04 16:12:55 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"


void parse_line(char *line, t_scene *scene)
{
	if (line[0] == 'A')
		parse_ambient(line, scene);
	else if (line[0] == 'C')
		parse_camera(line, scene);
	else if (line[0] == 'L')
		parse_light(line, scene);
	else if (ft_strncmp(line, "sp", 2) == 0)
		parse_sphere(line, scene);
	else if (ft_strncmp(line, "pl", 2) == 0)
		parse_plane(line, scene);
	else if (ft_strncmp(line, "cy", 2) == 0)
		parse_cylinder(line, scene);
	else
	{
		ft_putstr_stderr("Error: Invalid object or malformed line");
		return;
	}
}

void parse_camera(char *line, t_scene *scene)
{
	char	**s;
	
	s = ft_split(line, ' ');
	if (!s || !s[1] || !s[2] || !s[3])
	{
		ft_putstr_stderr("Error: Camera line missing parameters");
		free_split(s);
		return;
	}
	scene->camera.view_point = parse_vector(s[1]);
	scene->camera.norm = v_unit(parse_vector(s[2]));
	scene->camera.fov_deg = ft_atoi(s[3]);
	scene->camera.fov_rad = scene->camera.fov_deg * (M_PI / 180.f);
	free_split(s);
}
