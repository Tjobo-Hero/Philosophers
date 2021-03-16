/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_think_sleep.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 13:24:12 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/16 12:22:41 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	dead_or_alive(t_data *philo)
{
	if (get_time(NULL) >= philo->time_eaten + philo->time_to_die)
	{
		print_function(DEAD, philo);
		if (sem_post(philo->sem_state) == -1)
			exit(1);
		exit(0);
		return (DEAD);
	}
	else
		return (ALIVE);
}

void	sleeping(unsigned long int sleep_time)
{
	unsigned long int	time_now;

	time_now = get_time(NULL);
	while (get_time(NULL) < time_now + sleep_time)
		usleep(100);
}

int	philo_go_sleep(t_data *philo)
{
	if (print_function(SLEEPING, philo))
		return (PRINT_ERROR);
	sleeping(philo->time_to_sleep);
	return (SUCCESS);
}

int	eat_check(t_data *philo, int num, int health)
{
	if (sem_wait(philo->sem_eat) == -1)
		return (SEM_WAIT_ERROR);
	if (num == EAT_CHECK)
	{
		philo->time_eaten = get_time(NULL);
		philo->eat_count++;
		if (sem_post(philo->sem_eat) == -1)
			return (SEM_POST_ERROR);
	}
	else
	{
		health = dead_or_alive(philo);
		if (health != DEAD && sem_post(philo->sem_eat) == -1)
			return (SEM_POST_ERROR);
		return (health);
	}
	return (SUCCESS);
}

int	philo_go_eat(t_data *philo)
{
	if (sem_wait(philo->total_forks) == -1)
		return (print_function(SEM_WAIT_ERROR, NULL));
	if (print_function(RIGHT_FORK, philo))
		return (PRINT_ERROR);
	if (sem_wait(philo->total_forks) == -1)
		return (print_function(SEM_WAIT_ERROR, NULL));
	if (print_function(LEFT_FORK, philo))
		return (PRINT_ERROR);
	if (eat_check(philo, EAT_CHECK, 0) != SUCCESS)
		return (FAILURE);
	if (print_function(EATING, philo))
		return (PRINT_ERROR);
	sleeping(philo->time_to_eat);
	if (sem_post(philo->total_forks) == -1)
		return (print_function(SEM_POST_ERROR, NULL));
	if (sem_post(philo->total_forks) == -1)
		return (print_function(SEM_POST_ERROR, NULL));
	return (SUCCESS);
}
