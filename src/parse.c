/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:03 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/05 14:48:19 by ykhattab         ###   ########.fr       */
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

void parse_scene_file(const char *filename, t_scene *scene)
{
    int fd = open_file(filename);
    char *line;

    // initialize scene with empty objects list
    scene->objects = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        // skip empty and commented out lines
        if (line[0] != '\0' && line[0] != '\n' && line[0] != '#') 
            parse_line(line, scene);
        free(line);
    }
    
    // Debug: Print scene information
    // printf("Scene after parsing:\n");
    // printf("Camera: pos=(%f,%f,%f), norm=(%f,%f,%f), fov=%d\n", 
    //        scene->camera.view_point.x, scene->camera.view_point.y, scene->camera.view_point.z,
    //        scene->camera.norm.x, scene->camera.norm.y, scene->camera.norm.z,
    //        scene->camera.fov_deg);
    // printf("Light: pos=(%f,%f,%f), ratio=%f\n", 
    //        scene->light.pos.x, scene->light.pos.y, scene->light.pos.z,
    //        scene->light.colour.ratio);
    // printf("Ambient: ratio=%f, color=(%d,%d,%d)\n", 
    //        scene->a_light.ratio, scene->a_light.r, scene->a_light.g, scene->a_light.b);
    
    // Debug: Print objects
    // t_obj *obj = scene->objects;
    // int count = 0;
    // while (obj) 
	// {
    //     printf("Object %d: type=%d, center=(%f,%f,%f)\n", 
    //            count++, obj->type, obj->center.x, obj->center.y, obj->center.z);
    //     obj = obj->next;
    // }
    close(fd);
}
