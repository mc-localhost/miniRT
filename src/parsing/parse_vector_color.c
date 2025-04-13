/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:49:12 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/13 12:04:52 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_colour	parse_colour(char *string)
{
	t_colour	c;
	char		**s;
	char		*trimmed;

	trimmed = ft_strtrim(string, " \n");
	s = ft_split(trimmed, ',');
	free(trimmed);
	if (!s || !s[0] || !s[1] || !s[2] || s[3] || !is_valid_component(s[0], &c.r)
		|| !is_valid_component(s[1], &c.g) || !is_valid_component(s[2], &c.b))
	{
		if (s)
			free_split(s);
		return (INVALID_COL);
	}
	free_split(s);
	return (c);
}

t_vec3	parse_vector(char *string)
{
	t_vec3	parsed_vector;
	char	**s;

	s = ft_split(string, ',');
	if (!s || !s[0] || !s[1] || !s[2] || s[3])
	{
		free_split(s);
		return (INVALID_VEC3);
	}
	if (!is_valid_float(s[0]) || !is_valid_float(s[1]) || !is_valid_float(s[2]))
	{
		free_split(s);
		return (INVALID_VEC3);
	}
	parsed_vector.x = ft_atof(s[0]);
	parsed_vector.y = ft_atof(s[1]);
	parsed_vector.z = ft_atof(s[2]);
	free_split(s);
	return (parsed_vector);
}

bool	validate_colour(t_colour colour)
{
	if (colour.r < 0 || colour.r > 255 || colour.g < 0 || colour.g > 255
		|| colour.b < 0 || colour.b > 255)
		return (false);
	return (true);
}

bool	is_valid_component(char *str, int *out)
{
	char	*trimmed;
	int		len;
	bool	result;

	trimmed = ft_strdup(str);
	if (!trimmed)
		return (false);
	len = ft_strlen(trimmed);
	while (len > 0 && (trimmed[len - 1] == ' ' || trimmed[len - 1] == '\n'))
		trimmed[--len] = '\0';
	if (!is_number(str))
	{
		free(trimmed);
		return (false);
	}
	*out = ft_atoi(str);
	result = (*out >= 0 && *out <= 255);
	free(trimmed);
	return (result);
}
