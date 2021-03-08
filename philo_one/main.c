/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 10:28:07 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/08 13:14:46 by timvancitte   ########   odam.nl         */
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

int	initialize_struct(int argc, char **argv, t_data *philo)
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
		philo[i].eat_max = (argc == 6) ? ft_atoi(argv[5]) : -1;
		philo[i].eat_count = 0;
		philo[i].time_stamp = get_the_time(NULL);
		philo[i].time_created = philo[i].time_stamp;
		i++;
	}
	return (0);
}


int		eat(t_data *philo)
{
	print_function(3, philo);
	usleep(philo->time_to_eat);
	return (0);
}

int		sleeping(t_data *philo)
{
	print_function(1, philo);
	usleep(philo->time_to_sleep);
	return (0);
}

void*	start_loop(void *philo_void)
{
	t_data	*philo;
	
	philo = philo_void;
	while (1)
	{	
		print_function(2, philo);
		eat(philo);
		sleeping(philo);
	}
}

void	start_pthreads(t_data *philo_s, pthread_t *philo_thread, int i)
{
	while (i < philo_s->total_p)
	{
		if (pthread_create(&philo_thread[i], NULL, start_loop, &philo_s[i]) != 0)
			return;
		usleep(1);
		i++;
	}
	// Check if Philosopher is alive 
	while (i >= 0)
	{
		pthread_join(philo_thread[i], NULL);
		i--;
	}
}

int	initialize_mutex(t_data *philo_s, int i)
{
	pthread_mutex_t	*mu_write;
	pthread_mutex_t	*mu_eat;

	philo_s->total_forks = malloc(sizeof(pthread_mutex_t) * (philo_s->total_p));
	mu_eat = malloc(sizeof(pthread_mutex_t));
	mu_write = malloc(sizeof(pthread_mutex_t));
	if (philo_s->total_forks == NULL || mu_eat == NULL || mu_write == NULL)
		return (printf("Malloc fail mutex\n"));
	if (pthread_mutex_init(mu_write, NULL)|| pthread_mutex_init(mu_eat, NULL))
		return (printf("Mutex init error eat and write\n"));
	while (i < philo_s->total_p)
	{
		philo_s[i].mu_eat = mu_eat;
		philo_s[i].mu_write = mu_write;
		if (pthread_mutex_init(&philo_s->total_forks[i], NULL))
			return (printf("Mutex init error philo forks\n"));
		philo_s[i].left_fork = &philo_s->total_forks[i];
		if (i != 0) // Because the fork on the right of philo[0] has not yet been created
			philo_s->right_fork = &philo_s->total_forks[i - 1];
		i++;
		if (i == philo_s->total_p) // Fork on the right side of the first philosopher has been creatd and now we can link them
			philo_s[0].right_fork = &philo_s->total_forks[i - 1];
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*philo_s;
	pthread_t	*philo_thread;
	
	if (argc != 5 && argc != 6)
		return(printf("Error arguments\n"));
	else
	{
		if (parser(argc, argv))
			return (printf("Error input\n"));
		philo_s = malloc(sizeof(t_data) * ft_atoi(argv[1]));
		if (!philo_s)
			return (printf("malloc fail struct main\n"));
		if (initialize_struct(argc, argv, philo_s))
			return (printf("initialize fail\n"));
		if (initialize_mutex(philo_s, 0))
		{
			// Free struct that has been initialized
			return (printf("Initialize mutex error\n"));
		}
		philo_thread = malloc(sizeof(pthread_t) * (philo_s->total_p + 1));
		if (philo_thread == NULL)
		{
			printf("Pthread malloc fail\n");
			// Free struct that has been initialized
			// Free Mutex that has been initialized
		}
		start_pthreads(philo_s, philo_thread, 0);
	}
	return (0);
}