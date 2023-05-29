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

void	print_death(t_shared *shared, t_philo *philo)
{
	pthread_mutex_lock(&shared->print_lock);
	printf("%lld\t\t%d %s",
		   get_timestamp(philo->info->start_time), philo->id, STATE_DIED);
	pthread_mutex_unlock(&shared->print_lock);
}

void	print_state(t_shared *shared, t_philo *philo, char *state)
{
	pthread_mutex_lock(&shared->sim.lock);
	if (shared->sim.sim_status == ON)
	{
		if(get_time() > philo->death_time.death_time)
		{
			print_death(shared, philo);
			shared->sim.sim_status = OFF;
			pthread_mutex_unlock(&shared->sim.lock);
			return ;
		}
		pthread_mutex_lock(&shared->print_lock);
		printf("%lld\t\t%d %s",
			get_timestamp(philo->info->start_time), philo->id, state);
		pthread_mutex_unlock(&shared->print_lock);
	}
	pthread_mutex_unlock(&shared->sim.lock);
}

void	act_delay(long long int	time)
{
	long long int	temp;

	temp = get_time();
	while (get_time() - temp < time)
		usleep(1000);
}

void	act_eat(t_shared *shared, t_philo *philo)
{
	pthread_mutex_lock(&philo->death_time.lock);
	philo->death_time.death_time = get_time() + philo->info->time_to_die;
	pthread_mutex_unlock(&philo->death_time.lock);
	print_state(shared, philo, STATE_EAT);
	++philo->ate_cnt;
	if (philo->ate_cnt
		== philo->info->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&shared->full_philo_cnt.lock);
		++shared->full_philo_cnt.full_philo_cnt;
		if (shared->full_philo_cnt.full_philo_cnt
			== philo->info->number_of_philosophers)
		{
			pthread_mutex_lock(&(shared->sim.lock));
			shared->sim.sim_status = OFF;
			pthread_mutex_unlock(&(shared->sim.lock));
		}
		pthread_mutex_unlock(&shared->full_philo_cnt.lock);
	}
	act_delay(philo->info->time_to_eat);
}


void	act_take_fork_left(t_shared *shared, t_philo *philo)
{
	pthread_mutex_lock(&(shared->forks + philo->left_fork_id)->lock);
	(shared->forks + philo->left_fork_id)->fork_status = USING;
	print_state(shared, philo, STATE_TAKE);
	pthread_mutex_lock(&(shared->forks + philo->right_fork_id)->lock);
	(shared->forks + philo->right_fork_id)->fork_status = USING;
	print_state(shared, philo, STATE_TAKE);
	act_eat(shared, philo);
	(shared->forks + philo->right_fork_id)->fork_status = FREE;
	pthread_mutex_unlock(&(shared->forks + philo->right_fork_id)->lock);
	(shared->forks + philo->left_fork_id)->fork_status = FREE;
	pthread_mutex_unlock(&(shared->forks + philo->left_fork_id)->lock);
}


void	act_take_fork_right(t_shared *shared, t_philo *philo)
{
	pthread_mutex_lock(&(shared->forks + philo->right_fork_id)->lock);
	(shared->forks + philo->right_fork_id)->fork_status = USING;
	print_state(shared, philo, STATE_TAKE);
	pthread_mutex_lock(&(shared->forks + philo->left_fork_id)->lock);
	(shared->forks + philo->left_fork_id)->fork_status = USING;
	print_state(shared, philo, STATE_TAKE);
	act_eat(shared, philo);
	(shared->forks + philo->left_fork_id)->fork_status = FREE;
	pthread_mutex_unlock(&(shared->forks + philo->left_fork_id)->lock);
	(shared->forks + philo->right_fork_id)->fork_status = FREE;
	pthread_mutex_unlock(&(shared->forks + philo->right_fork_id)->lock);
}

void	act_sleep_and_think(t_shared *shared, t_philo *philo)
{
	print_state(shared, philo, STATE_SLEEP);
	act_delay(philo->info->time_to_sleep);
	print_state(shared, philo, STATE_THINK);
	usleep(500);
}

t_sim_status	check_sim_status(t_shared *shared)
{
	t_sim_status	status;
	pthread_mutex_lock(&(shared->sim.lock));
	status = shared->sim.sim_status;
	pthread_mutex_unlock(&(shared->sim.lock));
	return (status);
}
void	*philo_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time() < philo->info->start_time)
		usleep(1000);
	if (philo->id % 2)
	{
		usleep(700);
		while (1)
		{
			act_take_fork_left(&(philo->info->shared), philo);
			act_sleep_and_think(&(philo->info->shared), philo);
		}
	}
	else
	{
		while (1)
		{
			act_take_fork_right(&(philo->info->shared), philo);
			act_sleep_and_think(&(philo->info->shared), philo);
		}
	}
	return (0);
}

void	monitor(t_shared *shared, t_philo *philos)
{
	int		i;

	i = 0;
	while (1)
	{
		if (check_sim_status(shared) == OFF)
			break ;
		pthread_mutex_lock(&(philos + i)->death_time.lock);
		if (get_time() > (philos + i)->death_time.death_time)
		{
			pthread_mutex_lock(&(shared->sim.lock));
			if (shared->sim.sim_status == OFF)
			{
				pthread_mutex_unlock(&(shared->sim.lock));
				pthread_mutex_unlock(&(philos + i)->death_time.lock);
				break;
			}
			shared->sim.sim_status = OFF;
			pthread_mutex_lock(&shared->print_lock);
			printf("%lld\t\t%d %s",
				   get_timestamp(philos->info->start_time), i + 1, STATE_DIED);
			pthread_mutex_unlock(&(shared->sim.lock));
			pthread_mutex_unlock(&shared->print_lock);
			pthread_mutex_unlock(&(philos + i)->death_time.lock);
			break ;
		}
		pthread_mutex_unlock(&(philos + i)->death_time.lock);
		++i;
		if (i == philos->info->number_of_philosophers)
			i = 0;
	}
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

	monitor(&info->shared, philos);
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
	return (destroy_n_free(&info, philos, simulate(&info, philos)));
}