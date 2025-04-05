/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:03 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/05 23:03:12 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

char	*get_next_line(int fd);

int	rt_file(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3)
		return (EXIT_FAILURE);
	return (ft_strncmp(file + len - 3, ".rt", 3));
}

int open_file(const char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (-1);
    }
    return (fd);
}

int parse_scene_file(const char *filename, t_scene *scene)
{
    int fd;
    char *line;
	int ambient_found = 0;
	int camera_found = 0;
	int light_found = 0;
	
	fd = open_file(filename);
	if (fd < 0)
		return (error_message("Failed to open file."));
    scene->objects = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        // skip empty and commented out lines
        if (line[0] != '\0' && line[0] != '\n' && line[0] != '#') 
        {
			if (parse_line(line, scene))
				{
					free(line);
					close(fd);
					free_scene(scene); // recheck if we are double freeing
					return error_message("Error: failed to parse line.");
				}
				if (line[0] == 'A')
					ambient_found++;
				else if (line[0] == 'C')
					camera_found++;
				else if (line[0] == 'L')
					light_found++;
			}
        free(line);
    }
	if (ambient_found != 1)
		return error_message("Error: Expected exactly one ambient object.");
	if (camera_found != 1)
		return error_message("Error: Expected exactly one camera object.");
	if (light_found != 1)
		return error_message("Error: Expected exactly one light object.");
	
    close(fd);
	return (EXIT_SUCCESS);
}
