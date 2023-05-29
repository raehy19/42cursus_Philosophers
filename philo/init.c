/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 09:45:51 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/29 10:30:40 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(t_info *info)
{
	int		i;

	info->shared.forks = calloc(info->number_of_philosophers, sizeof(t_fork));
	if (!info->shared.forks)
		return (ERR_MALLOC);
	i = -1;
	while (++i < info->number_of_philosophers)
	{
		(info->shared.forks + i)->fork_status = FREE;
		if (pthread_mutex_init(&(info->shared.forks + i)->lock, NULL))
			return (ERR_MUTEX_INIT);
	}
	info->shared.sim.sim_status = ON;
	info->shared.full_philo_cnt.full_philo_cnt = 0;
	if (pthread_mutex_init(&(info->shared.sim.lock), NULL)
		|| pthread_mutex_init(&(info->shared.full_philo_cnt.lock), NULL)
		|| pthread_mutex_init(&(info->shared.print_lock), NULL))
		return (ERR_MUTEX_INIT);
	info->start_time = get_time() + START_DELAY;
	return (0);
}

int	init_philos(t_info *info, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		(philos + i)->thread_id = 0;
		(philos + i)->info = info;
		(philos + i)->id = i + 1;
		if (i + 1 < info->number_of_philosophers)
			(philos + i)->left_fork = &(info->shared.forks[i + 1]);
		(philos + i)->right_fork = &(info->shared.forks[i]);
		(philos + i)->ate_cnt = 0;
		(philos + i)->death_time.death_time
			= info->start_time + info->time_to_die;
		if (pthread_mutex_init(&(philos + i)->death_time.lock, NULL))
			return (ERR_MUTEX_INIT);
		++i;
	}
	(philos + --i)->left_fork = &(info->shared.forks[0]);
	return (0);
}
