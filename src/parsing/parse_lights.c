/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:57:21 by yousef            #+#    #+#             */
/*   Updated: 2025/04/08 14:50:22 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	parse_light(char *line, t_scene *scene)
{
	char	**s;

	s = validate_params(line, 4, "Error\nLight line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	scene->light.pos = parse_vector(s[1]);
	if (!is_valid_ratio(ft_atof(s[2])))
	{
		free_split(s);
		return (error_message("Error\nInvalid light ratio"));
	}
	scene->light.colour = parse_colour(s[3]);
	if (!validate_colour(scene->light.colour))
	{
		free_split(s);
		return (error_message("Error\nInvalid colour in light"));
	}
	scene->light.colour.ratio = ft_atof(s[2]);
	free_split(s);
	return (EXIT_SUCCESS);
}

int	parse_ambient(char *line, t_scene *scene)
{
	char	**s;
	float	ratio;

	s = validate_params(line, 3, "Error\nAmbient line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	ratio = ft_atof(s[1]);
	if (!is_valid_ratio(ratio))
	{
		free_split(s);
		return (error_message("Error\nInvalid ambient light ratio"));
	}
	scene->a_light = parse_colour(s[2]);
	scene->a_light.ratio = ratio;
	if (!validate_colour(scene->a_light))
	{
		free_split(s);
		return (error_message("Error\nInvalid colour in ambient light"));
	}
	free_split(s);
	return (EXIT_SUCCESS);
}
