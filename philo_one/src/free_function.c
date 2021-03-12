/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_function.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 12:36:51 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/12 13:16:27 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_struct(t_data *philo_s)
{
	free(philo_s->state);
	free(philo_s);
}

void	free_mutex(t_data *philo_s, pthread_t *philo_thread, int i, int thread)
{
	while (i < philo_s->total_p)
	{
		if (pthread_mutex_destroy(philo_s[i].left_fork) != 0)
			printf("Error: Mutex destroy fail\n");
		i++;
	}
	if (pthread_mutex_destroy(philo_s[0].mu_eat) != 0)
		printf("Error: Mutex destroy fail");
	if (pthread_mutex_destroy(philo_s[0].mu_write) != 0)
		printf("Error: Mutex destroy fail");
	if (thread)
		free(philo_thread);
	free(philo_s->mu_eat);
	free(philo_s->mu_write);
	free(philo_s->total_forks);
}

int	free_function(t_data *philo_s, pthread_t *philo_thread, int stage)
{
	if (stage == 1)
	{
		free_struct(philo_s);
		printf("Error: initialize mutex fail\n");
	}
	else if (stage == 2)
	{
		free_mutex(philo_s, NULL, 0, 0);
		free_struct(philo_s);
		printf("Error: initialize thread fail\n");
	}
	else
	{
		free_mutex(philo_s, philo_thread, 0, 1);
		free_struct(philo_s);
	}
	return (1);
}
