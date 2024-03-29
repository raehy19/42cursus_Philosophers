/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 02:55:46 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/29 10:38:46 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_shared *shared, t_philo *philos)
{
	int		i;

	i = 0;
	while (1)
	{
		if (check_sim_status(shared) == sim_off)
			break ;
		pthread_mutex_lock(&(philos + i)->death_time.lock);
		if (get_time() >= (philos + i)->death_time.death_time)
		{
			found_dead(shared, (philos + i));
			break ;
		}
		pthread_mutex_unlock(&(philos + i)->death_time.lock);
		++i;
		if (i == philos->info->number_of_philosophers)
			i = 0;
		usleep(100);
	}
}

int	start_sim(t_info *info, t_philo *philos)
{
	int		i;

	i = -1;
	if (info->number_of_philosophers % 2)
	{
		while (++i < info->number_of_philosophers)
		{
			if (pthread_create(&(philos + i)->thread_id,
					NULL, routine_odd, (philos + i)))
				return (ERR_THREAD_CREATE);
		}
		monitor(&info->shared, philos);
	}
	else
	{
		while (++i < info->number_of_philosophers)
		{
			if (pthread_create(&(philos + i)->thread_id,
					NULL, routine_even, (philos + i)))
				return (ERR_THREAD_CREATE);
		}
		monitor(&info->shared, philos);
	}
	return (0);
}

int	simulate(t_info	*info, t_philo *philos)
{
	if (init_info(info) || init_philos(info, philos))
		return (destroy_n_free(info, philos, ERR_INIT));
	if (info->number_of_philosophers == 1)
	{
		if (pthread_create(&(philos)->thread_id, NULL, routine_one, philos))
			return (ERR_THREAD_CREATE);
		monitor(&info->shared, philos);
	}
	else
	{
		if (start_sim(info, philos))
			return (ERR_THREAD_CREATE);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	static t_info	info;
	t_philo			*philos;

	if (argc != 5 && argc != 6)
		return (ft_arg_cnt_err());
	info.number_of_philosophers = ft_atoi(*(argv + 1));
	info.time_to_die = ft_atoi(*(argv + 2));
	info.time_to_eat = ft_atoi(*(argv + 3));
	info.time_to_sleep = ft_atoi(*(argv + 4));
	if (argc == 6)
		info.number_of_times_each_philosopher_must_eat = ft_atoi(*(argv + 5));
	if (ft_check_arg(argc, &info))
		return (ft_arg_val_err());
	philos = ft_calloc(info.number_of_philosophers, sizeof(t_philo));
	if (!philos)
		return (ERR_MALLOC);
	return (destroy_n_free(&info, philos, simulate(&info, philos)));
}
