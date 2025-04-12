/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:43:13 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/12 18:56:41 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_obj	*create_object(t_type type, t_vec3 norm, float diameter, float h)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->norm = norm;
	obj->diameter = diameter;
	obj->r = diameter / 2.f;
	obj->h = h;
	obj->next = NULL;
	return (obj);
}

void	add_object(t_obj **list, t_obj *new_obj)
{
	t_obj	*temp;

	if (!*list)
	{
		*list = new_obj;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_obj;
}

char	*normalize_whitespace(const char *str)
{
	char	*result;
	char	*dst;
	int		in_space;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	dst = result;
	in_space = 0;
	while (*str)
	{
		if (ft_isspace(*str) && !in_space)
		{
			*dst++ = ' ';
			in_space = 1;
		}
		else if (!ft_isspace(*str))
		{
			*dst++ = *str;
			in_space = 0;
		}
		str++;
	}
	*dst = '\0';
	return (result);
}

int	rt_file(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3)
		return (EXIT_FAILURE);
	return (ft_strncmp(file + len - 3, ".rt", 3));
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_stderr("Error\nFailed to open file");
		return (-1);
	}
	return (fd);
}
