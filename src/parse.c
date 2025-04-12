/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:03 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/12 01:54:45 by ykhattab         ###   ########.fr       */
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
		ft_putstr_stderr("Error\nFailed to open file");
        return (-1);
    }
    return (fd);
}

int parse_scene_file(const char *filename, t_scene *scene)
{
    int		fd;
    char	*line;
    int		counts[3] = {0, 0, 0}; // A, C, L

    fd = open_file(filename);
    if (fd < 0)
        return (error_message("Error\nFailed to open file."));
    scene->objects = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] && line[0] != '\n' && line[0] != '#')
        {
            if (parse_line(line, scene))
            {
                free(line);
                close(fd);
                return (EXIT_FAILURE);
            }
            if (line[0] == 'A')
				counts[0]++;
            else if (line[0] == 'C')
				counts[1]++;
            else if (line[0] == 'L')
				counts[2]++;
        }
        free(line);
    }
    close(fd);
    if (counts[0] != 1 || counts[1] != 1 || counts[2] != 1)
        return (error_message("Error\nExpected exactly one ambient/camera/light object."));
    return (EXIT_SUCCESS);
}
