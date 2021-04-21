/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 12:07:33 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/04/21 09:50:55 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	unlink_old_sempahores(void)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_WRITE);
}

int	initialize_semaphore(t_data *philo_s, int i)
{
	unlink_old_sempahores();
	philo_s->total_forks = sem_open(SEM_FORK, O_CREAT,
			0600, philo_s->total_p);
	philo_s->sem_eat = sem_open(SEM_EAT, O_CREAT, 0600, 1);
	philo_s->sem_write = sem_open(SEM_WRITE, O_CREAT, 0600, 1);
	if (philo_s[i].total_forks == SEM_FAILED
		|| philo_s[i].sem_eat == SEM_FAILED
		|| philo_s[i].sem_write == SEM_FAILED)
		return (SEM_ERROR);
	while (i < philo_s->total_p)
	{
		philo_s[i].total_forks = philo_s->total_forks;
		philo_s[i].sem_eat = philo_s->sem_eat;
		philo_s[i].sem_write = philo_s->sem_write;
		i++;
	}
	return (0);
}

int	initialize_struct(int argc, char **argv, t_data *philo, int i)
{
	int	total_philosophers;
	int	*state;

	state = malloc(sizeof(int));
	if (!state)
		return (printf("Malloc fail\n"));
	*state = ALIVE;
	total_philosophers = ft_atoi(argv[1]);
	while (i < total_philosophers)
	{
		philo[i].state = state;
		philo[i].total_p = ft_atoi(argv[1]);
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].p_nb = i;
		philo[i].eat_max = -1;
		if (argc == 6)
			philo[i].eat_max = ft_atoi(argv[5]);
		philo[i].eat_count = 0;
		philo[i].time_eaten = get_time(NULL);
		philo[i].time_created = philo[i].time_eaten;
		i++;
	}
	return (0);
}
