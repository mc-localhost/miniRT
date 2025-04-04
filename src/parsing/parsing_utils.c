/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:48:58 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/04 16:51:52 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"


void	free_split(char **split)
{
	int i = 0;
	if (!split)
		return;
	while (split[i])
		free(split[i++]);
	free(split);
}

bool is_number(char *str)
{
	if (!str || !*str)
	{
		return (false);
	}
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}


bool is_valid_ratio(float f)
{
	return (f >= 0.0f && f <= 1.0f);
}
