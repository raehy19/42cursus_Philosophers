/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 09:47:16 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/29 10:30:56 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
