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

int	init_info(t_info *info)
{
	int		i;

	info->shared.forks = calloc(info->number_of_philosophers, sizeof(t_fork));
	if (!info->shared.forks)
		return (ERR_MALLOC);
	i = 0;
	while (i < info->number_of_philosophers)
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
	info->start_time = ft_get_time() + START_DELAY;
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
		(philos + i)->left_fork_id = i + 1;
		(philos + i)->right_fork_id = i;
		(philos + i)->ate_cnt = 0;
		(philos + i)->death_time.death_time = info->start_time + info->time_to_die;
		if (pthread_mutex_init(&(philos + i)->death_time.lock, NULL))
			return (ERR_MUTEX_INIT);
		++i;
	}
	(philos + --i)->left_fork_id = 0;
	return (0);
}

int	destroy_n_free(t_info *info, t_philo *philos, int exit_code)
{
	int	i;

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
	if (philos)
	{
		i = -1;
		while (++i < info->number_of_philosophers)
			pthread_mutex_destroy(&(philos + i)->death_time.lock);
		pthread_join((philos + i)->thread_id, NULL);
	}
	free(philos);
	return (exit_code);
}

void	*philo_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{

	}
	return (0);
}

int	simulate(t_info	*info, t_philo *philos)
{
	int		i;

	if (init_info(info) || init_philos(info, philos))
		return (destroy_n_free(info, philos, ERR_INIT));
	i = -1;
	while (++i < info->number_of_philosophers)
	{
		if (pthread_create(&philos->thread_id, NULL, philo_act, (philos + i)))
			return (ERR_THREAD_CREATE);
	}
	// monitoring
	return (0);
}

int	main(int argc, char **argv)
{
	static t_info	info;
	t_philo			*philos;

	if (argc != 5 && argc != 6)
		return (ft_arg_err());
	info.number_of_philosophers = ft_atoi(*(argv + 1));
	info.time_to_die = ft_atoi(*(argv + 2));
	info.time_to_eat = ft_atoi(*(argv + 3));
	info.time_to_sleep = ft_atoi(*(argv + 4));
	if (argc == 6)
		info.number_of_times_each_philosopher_must_eat = ft_atoi(*(argv + 5));
	if (ft_check_arg(argc, &info))
		return (ft_arg_err());
	philos = ft_calloc(info.number_of_philosophers, sizeof(t_philo));
	if (!philos)
		return (ERR_MALLOC);

	printf("%d %d %d %d %d\n",info.number_of_philosophers, info.time_to_die, info.time_to_eat, info.time_to_sleep, info.number_of_times_each_philosopher_must_eat);
	return (destroy_n_free(&info, philos, simulate(&info, philos)));
}