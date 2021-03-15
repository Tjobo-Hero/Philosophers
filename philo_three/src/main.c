/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 10:28:07 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/15 17:53:09 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*check_state(void *philo_void)
{
	t_data	*philo;

	philo = philo_void;
	while (1)
		eat_check(philo, 0, 0);
	return (NULL);
}

void	*check_thread(void *philo_s_void)
{
	t_data *philo_s;
	int		i;

	philo_s = philo_s_void;
	i = 0;
	if (sem_wait(philo_s->sem_state) == -1)
	{
		print_function(SEM_WAIT_ERROR, NULL);
		return (NULL);
	}
	while (i < philo_s->total_p)
	{
		kill(philo_s[i].pid, SIGTERM);
		i++;
	}
	return (NULL);
}

void	*philo_loop(void *philo_void)
{
	t_data	*philo;

	philo = philo_void;
	while (1)
	{	
		if (philo_go_eat(philo) != SUCCESS)
			return (NULL);
		if (philo_go_sleep(philo) != SUCCESS)
			return (NULL);
		if (print_function(THINKING, philo))
			return (NULL);
		if (philo->eat_max == philo->eat_count)
		{
			sem_post(philo->sem_state);
			exit(0);
		}
	}
	return (NULL);
}

void	start_pthreads(t_data *philo_s, pthread_t *philo_thread, int i)
{
	while (i < philo_s->total_p)
	{
		philo_s[i].pid = fork();
		sleeping(1);
		if (!philo_s[i].pid)
		{
			if (pthread_create(&philo_thread[i], NULL, check_state, &philo_s[i]))
				return ;
			philo_loop(&philo_s[i]);
		}
		i++;
	}
	if (pthread_create(&philo_thread[i], NULL, check_thread, philo_s))
		return ;
	while (i >= 0)
	{
		pthread_join(philo_thread[i], NULL);
		i--;
	}
	pid_action(philo_s, i);
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
		if (initialize_semaphore(philo_s, 0))
			return (free_function(philo_s, NULL, 1));
		philo_thread = malloc(sizeof(pthread_t) * (philo_s->total_p + 1));
		if (!philo_thread)
			return (free_function(philo_s, NULL, 2));
		start_pthreads(philo_s, philo_thread, 0);
		free_function(philo_s, philo_thread, 0);
	}
	return (0);
}
