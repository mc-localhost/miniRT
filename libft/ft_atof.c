/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:09:00 by ykhattab          #+#    #+#             */
/*   Updated: 2025/04/12 01:22:24 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_sign(const char **str)
{
    int	sign;

    sign = 1;
    while (ft_isspace(**str))
        (*str)++;
    if (**str == '-' || **str == '+')
    {
        if (**str == '-')
            sign = -1;
        (*str)++;
    }
    return (sign);
}

static double	parse_integer(const char **str)
{
    double	result;

    result = 0.0;
    while (**str >= '0' && **str <= '9')
    {
        result = result * 10.0 + (**str - '0');
        (*str)++;
    }
    return (result);
}

static double	parse_fraction(const char **str)
{
    double	fraction;
    int		div;

    fraction = 0.0;
    div = 1;
    if (**str == '.')
    {
        (*str)++;
        while (**str >= '0' && **str <= '9')
        {
            fraction = fraction * 10.0 + (**str - '0');
            div *= 10;
            (*str)++;
        }
        if (div > 1)
            fraction /= div;
    }
    return (fraction);
}

double	ft_atof(const char *str)
{
    double	result;
    double	fraction;
    int		sign;

    if (!str)
        return (0.0);
    sign = parse_sign(&str);
    result = parse_integer(&str);
    fraction = parse_fraction(&str);
    return ((result + fraction) * sign);
}
