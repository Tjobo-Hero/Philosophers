/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 10:28:51 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/15 16:03:37 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define SEM_FORK "forks"
# define SEM_EAT "eat"
# define SEM_WRITE "write"
# define SEM_STATE "state"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>

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
	SEM_WAIT_ERROR,
	SEM_POST_ERROR,
	SEM_ERROR,
	PRINT_ERROR,
	EAT_CHECK,
	ALIVE_CHECK,
	FREE_STRUCT,
	FREE_MUTEX,
};

typedef struct s_data
{
	int					total_p;
	int					p_nb;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_max;
	int					eat_count;
	unsigned long int	time_eaten;
	unsigned long int	time_created;
	sem_t				*total_forks;
	sem_t				*sem_eat;
	sem_t				*sem_write;
	sem_t				*sem_state;
	int					pid;
}						t_data;

/* utils.c */
int						ft_atoi(const char *str);
unsigned long int		get_time(t_data *philo);
int						print_function(int num, t_data *philo);
int						dead_or_alive(t_data *philo);
int						print_function(int num, t_data *philo);

/* free_function.c */
int						free_function(t_data *philo_s, pthread_t
							*philo_thread, int stage);

/* eating_thinking_sleeping.c */
int						philo_go_eat(t_data *philo);
int						eat_check(t_data *philo, int num, int health);
void					sleeping(unsigned long int sleep_time);
int						philo_go_sleep(t_data *philo);

/* parser.c */
int						parser(int argc, char **argv);

/* initialize.c */
int						initialize_semaphore(t_data *philo_s, int i);
int						initialize_struct(int argc, char **argv,
							t_data *philo, int i);

/* pid action */
void					pid_action(t_data *philo_s, int i);

#endif
