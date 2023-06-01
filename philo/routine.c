/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:53:17 by rjeong            #+#    #+#             */
/*   Updated: 2023/06/01 16:47:29 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time() < philo->info->start_time)
		usleep(100);
	pthread_mutex_lock(&(philo->left_fork->lock));
	philo->left_fork->fork_status = use_fork;
	print_state(&(philo->info->shared), philo, STATE_TAKE);
	while (check_sim_status(&(philo->info->shared)) == sim_on)
		usleep(100);
	pthread_mutex_unlock(&(philo->left_fork->lock));
	return (0);
}

void	*routine_even(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time() < philo->info->start_time)
		usleep(100);
	if (philo->id % 2)
	{
		while (check_sim_status(&(philo->info->shared)) == sim_on)
		{
			act_take_fork_left(&(philo->info->shared), philo);
			act_sleep_and_think(&(philo->info->shared), philo);
			usleep(200);
		}
	}
	else
	{
		act_delay(philo->info->time_to_eat / 2 + 1);
		while (check_sim_status(&(philo->info->shared)) == sim_on)
		{
			act_take_fork_right(&(philo->info->shared), philo);
			act_sleep_and_think(&(philo->info->shared), philo);
			usleep(200);
		}
	}
	return (0);
}

void	*routine_odd(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time() < philo->info->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		act_delay(philo->info->time_to_eat / 2 + 1);
	while (check_sim_status(&(philo->info->shared)) == sim_on)
	{
		act_take_fork_left(&(philo->info->shared), philo);
		act_sleep_and_think(&(philo->info->shared), philo);
	}
	return (0);
}
