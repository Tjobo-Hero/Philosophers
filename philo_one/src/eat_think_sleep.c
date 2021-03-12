/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_think_sleep.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 13:24:12 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/12 10:54:21 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if (pthread_mutex_lock(philo->mu_eat) != 0)
		return (MUTEX_LOCK_ERROR);
	if (*philo->state != ALIVE)
		return (FAILURE);
	if (num == EAT_CHECK)
	{
		philo->time_eaten = get_time(NULL);
		philo->eat_count++;
		if (pthread_mutex_unlock(philo->mu_eat) != 0)
			return (MUTEX_UNLOCK_ERROR);
	}
	else
	{
		health = dead_or_alive(philo);
		if (pthread_mutex_unlock(philo->mu_eat))
			return (MUTEX_UNLOCK_ERROR);
		return (health);
	}
	return (SUCCESS);
}

void	mutex_unlock_at_death(t_data *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	philo_go_eat(t_data *philo)
{
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (print_function(MUTEX_LOCK_ERROR, NULL));
	if (*philo->state != ALIVE)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (FAILURE);
	}
	if (print_function(RIGHT_FORK, philo))
		return (PRINT_ERROR);
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (print_function(MUTEX_LOCK_ERROR, NULL));
	if (print_function(LEFT_FORK, philo))
		return (PRINT_ERROR);
	if (*philo->state != ALIVE || eat_check(philo, EAT_CHECK, 0) != SUCCESS)
	{
		mutex_unlock_at_death(philo);
		return (FAILURE);
	}
	if (print_function(EATING, philo))
		return (PRINT_ERROR);
	sleeping(philo->time_to_eat);
	if (pthread_mutex_unlock(philo->right_fork) != 0
		|| (pthread_mutex_unlock(philo->left_fork) != 0))
		return (print_function(MUTEX_UNLOCK_ERROR, NULL));
	return (SUCCESS);
}
