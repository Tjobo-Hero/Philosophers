/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 10:28:51 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/09 16:12:38 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

enum			e_state
{
	ALIVE,
	DEAD,
	SUCCESS,
	FAILURE,
	EATING,
	SLEEPING,
	THINKING,
	RIGHT_FORK,
	LEFT_FORK,
	MUTEX_LOCK_ERROR,
	MUTEX_UNLOCK_ERROR,
	PRINT_ERROR,
	CAN_I_EAT_CHECK,
	ALIVE_CHECK
};

typedef struct			s_data
{
	int					total_p;
	int					p_number;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_max;
	int					eat_count;
	unsigned long int	time_eaten;
	unsigned long int	time_created;
	pthread_mutex_t		*total_forks;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*mu_write;
	pthread_mutex_t		*mu_eat;
	int					*state;
}						t_data;


/* utils.c */
int						ft_atoi(const char *str);
unsigned long int 		get_the_time(t_data *philo);
int						print_function(int num, t_data *philo);

/* parser.c */
int						parser(int argc, char **argv);

/* initialize.c */
int						initialize_mutex(t_data *philo_s, int i);
int						initialize_struct(int argc, char **argv, t_data *philo, int i);
						

#endif
