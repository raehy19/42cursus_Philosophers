/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 09:45:21 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/29 09:45:22 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_arg_err(void)
{
	ft_putstr_fd("Please Check Program Arguments\n", STDERR_FILENO);
	return (ERR_ARG);
}

int	ft_check_arg(int argc, t_info *info)
{
	if (info->number_of_philosophers < 1
		|| info->time_to_die < 0
		|| info->time_to_eat < 0
		|| info->time_to_sleep < 0
		|| ((argc == 6) && (info->number_of_times_each_philosopher_must_eat < 1)))
		return (ERR_ARG);
	return (0);
}
