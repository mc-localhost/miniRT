/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:57:21 by yousef            #+#    #+#             */
/*   Updated: 2025/04/12 02:09:23 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	parse_light(char *line, t_scene *scene)
{
	char	**s;
	float	ratio;

	s = validate_params(line, 4, "Error\nLight line missing parameters");
	if (!s)
		return (EXIT_FAILURE);
	scene->light.pos = parse_vector(s[1]);
	if (!is_valid_float(s[2]))
		return (free_and_error(s, "Error\nInvalid format for light ratio"));
	ratio = ft_atof(s[2]);
	if (!is_valid_ratio(ratio))
		return (free_and_error(s, "Error\nInvalid light ratio"));
	scene->light.colour = parse_colour(s[3]);
	if (!validate_colour(scene->light.colour))
		return (free_and_error(s, "Error\nInvalid colour in light"));
	scene->light.colour.ratio = ratio;
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
	if (!is_valid_float(s[1]))
		return (free_and_error(s, "Error\nInvalid format for ambient light ratio"));
	ratio = ft_atof(s[1]);
	if (!is_valid_ratio(ratio))
		return (free_and_error(s, "Error\nInvalid ambient light ratio"));
	scene->a_light = parse_colour(s[2]);
	scene->a_light.ratio = ratio;
	if (!validate_colour(scene->a_light))
		return (free_and_error(s, "Error\nInvalid colour in ambient light"));
	free_split(s);
	return (EXIT_SUCCESS);
}
