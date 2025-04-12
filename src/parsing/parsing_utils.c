/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:48:58 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/12 00:33:28 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

bool	is_number(char *str)
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

bool	is_valid_ratio(float f)
{
	return (f >= 0.0f && f <= 1.0f);
}

bool	is_normalized(t_vec3 v)
{
	float len = v_len(v);
	return (fabs(len - 1.0f) < 1e-6);
}

bool	is_valid_float(char *str)
{
    int	i;
    int	dot_count;
    int	digit_found;

    if (!str || !*str)
        return (false);
    i = 0;
    dot_count = 0;
    digit_found = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            digit_found = 1;
        else if (str[i] == '.')
        {
            dot_count++;
            if (dot_count > 1)
                return (false);
        }
        else
            return (false);
        i++;
    }
    return (digit_found);
}
