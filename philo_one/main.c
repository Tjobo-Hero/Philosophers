/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 10:28:07 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/04 16:38:04 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int		parser(int argc, char **argv)
{
	int i;
	int y;

	i = 1;
	y = 0;
	while (i < argc)
	{
		y = 0;
		while (argv[i][y] != '\0')
		{
			if (!ft_is_digit(argv[i][y]))
				return(1);
			y++;
		}
		i++;
	}
	return (0);
}

int	initialize(int argc, char **argv, t_data *philo)
{
	int total_philosophers;
	int i;

	i = 0;
	total_philosophers = ft_atoi(argv[1]);
	while (i < total_philosophers)
	{
		philo[i].total_p = ft_atoi(argv[1]);
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].p_number = i;
		philo[i].eat_max = -1;
		philo[i].eat_count = 0;
		philo[i].time_stamp = get_the_time(NULL);
		philo[i].time_created = philo[i].time_stamp;
		if (argc == 6)
			philo[i].eat_max = ft_atoi(argv[5]);
		i++;
	}
	return (0);
}

void*	start_loop(t_data *philo)
{
	
	while (1)
	{
		
	}
}

void	starting_threads(t_data *philo, pthread_t *main_thread, int i)
{
	while (i < philo->total_p)
	{
		if (pthread_create(&main_thread[i], NULL, &start_loop, philo) != 0)
			return (NULL);
		
	}
}

int	main(int argc, char **argv)
{
	t_data		*philo;
	pthread_t	main_thread;
	
	if (argc != 5 && argc != 6)
		return(printf("Error arguments\n"));
	else
	{
		if (parser(argc, argv))
			return (printf("Error input\n"));
		philo = malloc(sizeof(t_data) * ft_atoi(argv[1]));
		if (!philo)
			return (printf("malloc fail struct main\n"));
		if (initialize(argc, argv, philo))
			return (printf("initialize fail\n"));
		main_thread = malloc(sizeof(pthread_t) * (philo[1].total_p));
		starting_threads(philo, main_thread, 0);
	}
	return (0);
}