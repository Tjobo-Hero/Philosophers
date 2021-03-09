/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 12:07:33 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/09 16:12:25 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialize_mutex(t_data *philo_s, int i)
{
	pthread_mutex_t	*mu_write;
	pthread_mutex_t	*mu_eat;

	philo_s->total_forks = malloc(sizeof(pthread_mutex_t) * (philo_s->total_p));
	mu_eat = malloc(sizeof(pthread_mutex_t));
	mu_write = malloc(sizeof(pthread_mutex_t));
	if (philo_s->total_forks == NULL || mu_eat == NULL || mu_write == NULL)
		return (printf("Malloc fail init mutex\n"));
	if (pthread_mutex_init(mu_write, NULL)|| pthread_mutex_init(mu_eat, NULL))
		return (printf("Mutex init error eat and write\n"));
	while (i < philo_s->total_p)
	{
		philo_s[i].mu_eat = mu_eat;
		philo_s[i].mu_write = mu_write;
		if (pthread_mutex_init(&philo_s->total_forks[i], NULL) != 0)
			return (printf("Mutex init error philo total forks\n"));
		philo_s[i].left_fork = &philo_s->total_forks[i];
		if (i != 0) // Because the fork on the right of philo[0] has not yet been created
			philo_s[i].right_fork = &philo_s->total_forks[i - 1];
		i++;
	}
	philo_s[0].right_fork = &philo_s->total_forks[i - 1]; // Fork on the right side of the first philosopher has been creatd and now we can link them
	return (0);
}

int	initialize_struct(int argc, char **argv, t_data *philo, int i)
{
	int total_philosophers;
	int *state;

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
		philo[i].p_number = i;
		philo[i].eat_max = (argc == 6) ? ft_atoi(argv[5]) : -1;
		philo[i].eat_count = 0;
		philo[i].time_eaten = get_the_time(NULL);
		philo[i].time_created = philo[i].time_eaten;
		i++;
	}
	return (0);
}
