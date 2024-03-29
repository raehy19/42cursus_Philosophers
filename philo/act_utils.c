/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:21:37 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/29 10:39:13 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	act_delay(long long int time)
{
	long long int	temp;

	temp = get_time();
	while (get_time() - temp < time)
		usleep(200);
}

t_sim_status	check_sim_status(t_shared *shared)
{
	t_sim_status	status;

	pthread_mutex_lock(&(shared->sim.lock));
	status = shared->sim.sim_status;
	pthread_mutex_unlock(&(shared->sim.lock));
	return (status);
}

void	print_state(t_shared *shared, t_philo *philo, char *state)
{
	pthread_mutex_lock(&shared->sim.lock);
	if (shared->sim.sim_status == sim_on)
	{
		pthread_mutex_lock(&(philo->death_time.lock));
		if (get_time() >= philo->death_time.death_time)
		{
			print_death(shared, philo);
			shared->sim.sim_status = sim_off;
			pthread_mutex_unlock(&shared->sim.lock);
			pthread_mutex_unlock(&(philo->death_time.lock));
			return ;
		}
		pthread_mutex_unlock(&(philo->death_time.lock));
		pthread_mutex_lock(&shared->print_lock);
		printf("%lld\t\t%d %s",
			get_timestamp(philo->info->start_time), philo->id, state);
		pthread_mutex_unlock(&shared->print_lock);
	}
	pthread_mutex_unlock(&shared->sim.lock);
}

void	print_death(t_shared *shared, t_philo *philo)
{
	pthread_mutex_lock(&shared->print_lock);
	printf("%lld\t\t%d %s",
		get_timestamp(philo->info->start_time), philo->id, STATE_DIED);
	pthread_mutex_unlock(&shared->print_lock);
}

void	found_dead(t_shared *shared, t_philo *philo)
{
	pthread_mutex_lock(&(shared->sim.lock));
	if (shared->sim.sim_status == sim_off)
	{
		pthread_mutex_unlock(&(shared->sim.lock));
		pthread_mutex_unlock(&(philo)->death_time.lock);
		return ;
	}
	shared->sim.sim_status = sim_off;
	pthread_mutex_lock(&shared->print_lock);
	printf("%lld\t\t%d %s",
		get_timestamp(philo->info->start_time), philo->id, STATE_DIED);
	pthread_mutex_unlock(&(shared->sim.lock));
	pthread_mutex_unlock(&shared->print_lock);
	pthread_mutex_unlock(&(philo)->death_time.lock);
}
