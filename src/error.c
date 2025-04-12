/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:42:57 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/12 01:44:52 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	error_message(char *str)
{
	ft_putendl_fd(str, 2);
	return (EXIT_FAILURE);
}

t_obj *error_return_null(char *err_msg)
{
    ft_putendl_fd(err_msg, 2);
    return (NULL);
}

int	free_and_error(char **split, char *msg)
{
    free_split(split);
    return (error_message(msg));
}
