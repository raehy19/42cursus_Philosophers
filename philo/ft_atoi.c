/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:34:36 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/28 17:38:47 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (1);
	return (0);
}

int	ft_cal_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (*(str + *i) == '+')
		++(*i);
	else if (*(str + *i) == '-')
	{
		sign = -1;
		++(*i);
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;
	unsigned long long	temp_result;

	i = 0;
	while (ft_isspace(*(str + i)))
		++i;
	sign = ft_cal_sign(str, &i);
	result = 0;
	while (ft_isdigit(*(str + i)))
	{
		temp_result = result * 10 + (unsigned long long)(*(str + i) - '0');
		if (temp_result < result
			|| (temp_result > LONG_MAX && sign > 0))
			return (-1);
		result = temp_result;
		++i;
	}
	return ((int)(result * sign));
}
