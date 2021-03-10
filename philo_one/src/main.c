/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 10:28:07 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/10 17:58:34 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_state(void *philo_s_void)
{
	t_data	*philo_s;
	int		i;

	philo_s = philo_s_void;
	i = 0;
	while (1)
	{
		if (i == philo_s->total_p)
			i = 0;
		if (eat_check(&philo_s[i], 0, 0) != ALIVE
			&& philo_s[i].eat_count != philo_s[i].eat_max)
		{
			print_function(DEAD, &philo_s[i]);
			return (NULL);
		}
		if (philo_s[i].eat_count == philo_s[i].eat_max)
			return (NULL);
		i++;
	}
	return (NULL);
}

void	*start_loop(void *philo_void)
{
	t_data	*philo;

	philo = philo_void;
	while (*philo->state != DEAD)
	{	
		if (philo_go_eat(philo) != SUCCESS || *philo->state != ALIVE)
			return (NULL);
		if (philo_go_sleep(philo) != SUCCESS || *philo->state != ALIVE)
			return (NULL);
		if (print_function(THINKING, philo) || *philo->state != ALIVE)
			return (NULL);
		if (philo->eat_max == philo->eat_count)
			return (NULL);
	}
	return (NULL);
}

void	start_pthreads(t_data *philo_s, pthread_t *philo_thread, int i)
{
	while (i < philo_s->total_p)
	{
		if (pthread_create(&philo_thread[i], NULL, start_loop, &philo_s[i]))
			return ;
		sleeping(1);
		i++;
	}
	if (pthread_create(&philo_thread[i], NULL, check_state, philo_s))
		return ;
	while (i >= 0)
	{
		pthread_join(philo_thread[i], NULL);
		i--;
	}
}

int	main(int argc, char **argv)
{
	t_data		*philo_s;
	pthread_t	*philo_thread;

	if (argc != 5 && argc != 6)
		return (printf("Error: invalid arguments\n"));
	else
	{
		if (parser(argc, argv))
			return (printf("Error input\n"));
		philo_s = malloc(sizeof(t_data) * ft_atoi(argv[1]));
		if (!philo_s)
			return (printf("Error: Malloc fail struct main\n"));
		if (initialize_struct(argc, argv, philo_s, 0))
			return (printf("Error: Struct initialize fail\n"));
		if (initialize_mutex(philo_s, 0))
			return (free_function(philo_s, NULL, 1));
		philo_thread = malloc(sizeof(pthread_t) * (philo_s->total_p + 1));
		if (!philo_thread)
			return (free_function(philo_s, NULL, 2));
		start_pthreads(philo_s, philo_thread, 0);
		free_function(philo_s, philo_thread, 0);
	}
	return (0);
}
