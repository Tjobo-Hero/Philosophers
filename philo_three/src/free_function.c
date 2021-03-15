/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 12:36:51 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/15 13:40:49 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_struct(t_data *philo_s)
{
	free(philo_s);
}

void	free_semaphore(t_data *philo_s, pthread_t *philo_thread, int thread)
{
	sem_close(philo_s->total_forks);
	sem_close(philo_s->sem_write);
	sem_close(philo_s->sem_eat);
	sem_close(philo_s->sem_state);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_STATE);
	if (thread)
		free(philo_thread);
}

int	free_function(t_data *philo_s, pthread_t *philo_thread, int stage)
{
	if (stage == 1)
	{
		free_struct(philo_s);
		printf("Error: initialize semaphore fail\n");
	}
	else if (stage == 2)
	{
		free_semaphore(philo_s, NULL, 0);
		free_struct(philo_s);
		printf("Error: initialize thread fail\n");
	}
	else
	{
		free_semaphore(philo_s, philo_thread, 1);
		free_struct(philo_s);
	}
	return (1);
}
