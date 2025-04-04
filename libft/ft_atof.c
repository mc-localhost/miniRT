/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:09:00 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/03 10:12:10 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		div;

	result = 0.0;
	fraction = 0.0;
	sign = 1;
	div = 1;

	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			fraction = fraction * 10.0 + (*str - '0');
			div *= 10;
			str++;
		}
		result += fraction / div;
	}
	return (result * sign);
}
