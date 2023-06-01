/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 09:45:21 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/29 10:39:10 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_arg_cnt_err(void)
{
	ft_putstr_fd("Please Check the Number of Program Arguments\n",
		STDERR_FILENO);
	return (ERR_ARG_VAL);
}

int	ft_arg_val_err(void)
{
	ft_putstr_fd("Please Check the Value of Program Arguments\n",
		STDERR_FILENO);
	return (ERR_ARG_CNT);
}

int	ft_check_arg(int argc, t_info *info)
{
	if (info->number_of_philosophers < 1
		|| info->time_to_die < 0
		|| info->time_to_eat < 1
		|| info->time_to_sleep < 1
		|| ((argc == 6)
			&& (info->number_of_times_each_philosopher_must_eat < 1)))
		return (ERR_ARG_CNT);
	return (0);
}

int	destroy_n_free(t_info *info, t_philo *philos, int exit_code)
{
	int	i;

	if (philos)
	{
		i = -1;
		while (++i < info->number_of_philosophers)
		{
			pthread_join((philos[i]).thread_id, NULL);
			pthread_mutex_destroy(&(philos + i)->death_time.lock);
		}
	}
	free(philos);
	if (info->shared.forks)
	{
		i = -1;
		while (++i < info->number_of_philosophers)
			pthread_mutex_destroy(&(info->shared.forks + i)->lock);
	}
	free(info->shared.forks);
	pthread_mutex_destroy(&info->shared.sim.lock);
	pthread_mutex_destroy(&info->shared.full_philo_cnt.lock);
	pthread_mutex_destroy(&info->shared.print_lock);
	return (exit_code);
}
