/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_only_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:53:17 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/30 20:53:18 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_act_one(void *arg)
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
