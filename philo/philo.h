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

# define START_DELAY		500

# define ERR_ARG			4
# define ERR_INIT			5
# define ERR_MALLOC			6
# define ERR_MUTEX_INIT		7
# define ERR_THREAD_CREATE	8

# define STATE_TAKE		"has taken a fork\n"
# define STATE_EAT		"is eating\n"
# define STATE_SLEEP	"is sleeping\n"
# define STATE_THINK	"is thinking\n"
# define STATE_DIED		"died\n"

typedef enum e_fork_status
{
	FREE,
	USING
}	t_fork_status;

typedef struct s_fork
{
	pthread_mutex_t	lock;
	t_fork_status	fork_status;
}	t_fork;

typedef enum e_sim_status
{
	ON,
	OFF
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

// utils
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
void			ft_putstr_fd(char *s, int fd);
long long int	get_time(void);
long long int	get_timestamp(long long int start_time);

// parse
int				ft_check_arg(int argc, t_info *info);
int				ft_arg_err(void);
int				destroy_n_free(t_info *info, t_philo *philos, int exit_code);

// init
int				init_info(t_info *info);
int				init_philos(t_info *info, t_philo *philos);

// act utils
void			act_delay(long long int time);
t_sim_status	check_sim_status(t_shared *shared);
int				print_state(t_shared *shared, t_philo *philo, char *state);
void			print_death(t_shared *shared, t_philo *philo);

// act
void			*philo_act(void *arg);

#endif
