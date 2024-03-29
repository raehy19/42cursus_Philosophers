/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:42:14 by rjeong            #+#    #+#             */
/*   Updated: 2023/05/29 10:39:05 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define START_DELAY		1000

# define ERR_ARG_CNT		4
# define ERR_ARG_VAL		5
# define ERR_INIT			6
# define ERR_MALLOC			7
# define ERR_MUTEX_INIT		8
# define ERR_THREAD_CREATE	9

# define STATE_TAKE			"has taken a fork\n"
# define STATE_EAT			"is eating\n"
# define STATE_SLEEP		"is sleeping\n"
# define STATE_THINK		"is thinking\n"
# define STATE_DIED			"died\n"

typedef enum e_fork_status
{
	free_fork,
	use_fork
}	t_fork_status;

typedef struct s_fork
{
	pthread_mutex_t	lock;
	t_fork_status	fork_status;
}	t_fork;

typedef enum e_sim_status
{
	sim_on,
	sim_off
}	t_sim_status;

typedef struct s_sim
{
	pthread_mutex_t	lock;
	t_sim_status	sim_status;
}	t_sim;

typedef struct s_full_philo_cnt
{
	pthread_mutex_t	lock;
	int				full_philo_cnt;
}	t_full_philo_cnt;

typedef struct s_shared
{
	t_fork				*forks;
	t_sim				sim;
	t_full_philo_cnt	full_philo_cnt;
	pthread_mutex_t		print_lock;
}	t_shared;

typedef struct s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long long int	start_time;
	t_shared		shared;
}	t_info;

typedef struct s_death_time
{
	pthread_mutex_t	lock;
	long long int	death_time;
}	t_death_time;

typedef struct s_philo
{
	pthread_t		thread_id;
	t_info			*info;
	unsigned int	id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				ate_cnt;
	t_death_time	death_time;
}	t_philo;

int				init_info(t_info *info);
int				init_philos(t_info *info, t_philo *philos);

void			*routine_odd(void *arg);
void			*routine_even(void *arg);
void			*routine_one(void *arg);

void			act_take_fork_left(t_shared *shared, t_philo *philo);
void			act_take_fork_right(t_shared *shared, t_philo *philo);
void			act_eat(t_shared *shared, t_philo *philo);
void			act_sleep_and_think(t_shared *shared, t_philo *philo);

void			act_delay(long long int time);
t_sim_status	check_sim_status(t_shared *shared);
void			print_state(t_shared *shared, t_philo *philo, char *state);
void			print_death(t_shared *shared, t_philo *philo);
void			found_dead(t_shared *shared, t_philo *philo);

int				ft_check_arg(int argc, t_info *info);
int				ft_arg_cnt_err(void);
int				ft_arg_val_err(void);
int				destroy_n_free(t_info *info, t_philo *philos, int exit_code);

int				ft_atoi(const char *str);

void			*ft_calloc(size_t count, size_t size);

void			ft_putstr_fd(char *s, int fd);

long long int	get_time(void);
long long int	get_timestamp(long long int start_time);

#endif
