/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:57:21 by yousef            #+#    #+#             */
/*   Updated: 2025/04/04 22:31:21 by ykhattab         ###   ########.fr       */
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

static t_obj	*parse_obj_params(char **s, t_type type, __attribute__((unused))t_scene *scene)
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

void	parse_sphere(char *line, t_scene *scene)
{
	char	**s;
	t_obj	*new_obj;

	s = validate_params(line, 4, "Error: Sphere line missing parameters");
	if (!s)
		return ;
	new_obj = parse_obj_params(s, SPHERE, scene);
	if (new_obj)
		add_object(&scene->objects, new_obj);
	free_split(s);
}

void	parse_plane(char *line, t_scene *scene)
{
	char	**s;
	t_obj	*new_obj;

	s = validate_params(line, 4, "Error: Plane line missing parameters");
	if (!s)
		return ;
	new_obj = parse_obj_params(s, PLANE, scene);
	if (new_obj)
		add_object(&scene->objects, new_obj);
	free_split(s);
}

void	parse_cylinder(char *line, t_scene *scene)
{
	char	**s;
	t_obj	*new_obj;

	s = validate_params(line, 6, "Error: Cylinder line missing parameters");
	if (!s)
		return ;
	new_obj = parse_obj_params(s, CYLINDER, scene);
	if (new_obj)
		add_object(&scene->objects, new_obj);
	free_split(s);
}

void	parse_light(char *line, t_scene *scene)
{
	char	**s;

	s = validate_params(line, 4, "Error: Light line missing parameters");
	if (!s)
		return ;
	scene->light.pos = parse_vector(s[1]);
	// printf("output of ratio after atof: %f", scene->light.colour.ratio);
	scene->light.colour = parse_colour(s[3]);
	scene->light.colour.ratio = ft_atof(s[2]);
	free_split(s);
}

void	parse_ambient(char *line, t_scene *scene)
{
	char	**s;
	float	ratio;

	s = validate_params(line, 3, "Error: Ambient line missing parameters");
	if (!s)
		return ;
	ratio = ft_atof(s[1]);
	if (!is_valid_ratio(ratio))
	{
		ft_putstr_stderr("Error: Invalid ambient light ratio");
		free_split(s);
		return ;
	}
	scene->a_light = parse_colour(s[2]);
	scene->a_light.ratio = ratio;
	if (!validate_colour(scene->a_light))
	{
		ft_putstr_stderr("Error: Invalid colour in ambient light");
		free_split(s);
		return ;
	}
	free_split(s);
}
