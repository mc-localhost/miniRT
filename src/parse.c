/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:03 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/12 18:25:00 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

char	*get_next_line(int fd);

static void	init_counts(int counts[3])
{
	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
}

static int	process_line(char *line, t_scene *scene, int counts[3])
{
	if (line[0] && line[0] != '\n' && line[0] != '#')
	{
		if (parse_line(line, scene))
			return (EXIT_FAILURE);
		if (line[0] == 'A')
			counts[0]++;
		else if (line[0] == 'C')
			counts[1]++;
		else if (line[0] == 'L')
			counts[2]++;
	}
	return (EXIT_SUCCESS);
}

static int	validate_scene_counts(int counts[3])
{
	if (counts[0] != 1 || counts[1] != 1 || counts[2] != 1)
		return (error_message("Error\nExpected exactly one \
			ambient/camera/light object."));
	return (EXIT_SUCCESS);
}

int	parse_scene_file(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;
	int		counts[3];
	int		result;

	init_counts(counts);
	fd = open_file(filename);
	if (fd < 0)
		return (error_message("Error\nFailed to open file."));
	scene->objects = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		result = process_line(line, scene, counts);
		free(line);
		if (result == EXIT_FAILURE)
		{
			close(fd);
			return (EXIT_FAILURE);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_scene_counts(counts));
}
