/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:03 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/05 21:34:28 by ykhattab         ###   ########.fr       */
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
        exit(EXIT_FAILURE);
    }
    return (fd);
}

int parse_scene_file(const char *filename, t_scene *scene)
{
    int fd;
    char *line;
	
	fd = open_file(filename);
	if (fd < 0)
		return (error_message("Failed to open file."));

    scene->objects = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        // skip empty and commented out lines
        if (line[0] != '\0' && line[0] != '\n' && line[0] != '#') 
            if (parse_line(line, scene))
				{
					free(line);
					close(fd);
					return error_message("Error: failed to parse line.");
				}
        free(line);
    }
    close(fd);
	return (EXIT_SUCCESS);
}
