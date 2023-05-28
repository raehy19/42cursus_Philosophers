/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 02:55:46 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/04 02:55:48 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "stdio.h"

int	ft_arg_err(void)
{
	ft_putstr_fd("Please Check Program Arguments\n", STDERR_FILENO);
	return(-1);
}

int	main(int argc, char **argv)
{
	static t_info	info;

	if (argc != 5 && argc != 6)
		return (ft_arg_err());
	info.number_of_philosophers = ft_atoi(*(argv + 1));
	info.time_to_die = ft_atoi(*(argv + 2));
	info.time_to_eat = ft_atoi(*(argv + 3));
	info.time_to_sleep = ft_atoi(*(argv + 4));
	if (argc == 6)
		info.number_of_times_each_philosopher_must_eat = ft_atoi(*(argv + 5));
	printf("%d %d %d %d %d\n",info.number_of_philosophers, info.time_to_die, info.time_to_eat, info.time_to_sleep, info.number_of_times_each_philosopher_must_eat);
	return (0);
}