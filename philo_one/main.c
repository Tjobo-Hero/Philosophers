/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 10:28:07 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/09 16:34:09 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int	dead_or_alive(t_data *philo)
{
	if (get_the_time(NULL) >= philo->time_eaten + philo->time_to_die)
		return (DEAD);
	else
		return (ALIVE);
}

int	print_function(int num, t_data *philo)
{
	if (pthread_mutex_lock(philo->mu_write) != 0)
		return (printf("Mutex write lock error\n"));
	if (num == MUTEX_LOCK_ERROR)
		return (printf("Mutex lock error\n"));
	else if (num == MUTEX_UNLOCK_ERROR)
		return (printf("Mutex unlock error\n"));
	else if (num == SLEEPING)
		printf("%lu - philo:[%i] is sleeping\n", get_the_time(philo), philo->p_number);
	else if (num == LEFT_FORK)
		printf("%lu - philo:[%i] has taken left fork\n", get_the_time(philo), philo->p_number);
	else if (num == RIGHT_FORK)
		printf("%lu - philo:[%i] has taken right fork\n", get_the_time(philo), philo->p_number);
	else if (num == EATING)
		printf("%lu - philo:[%i] is eating\n", get_the_time(philo), philo->p_number);
	else if (num == THINKING)
		printf("%lu - philo:[%i] is thinking\n", get_the_time(philo), philo->p_number);
	else if (num == DEAD)
		{
			*philo->state = DEAD;
			printf("%lu - philo:[%i] died\n", get_the_time(philo), philo->p_number);
		}
	if (pthread_mutex_unlock(philo->mu_write) != 0)
		return (printf("Mutex write unlock error\n"));
	return (0);
}

void	sleeping(unsigned long int sleep_time)
{
	unsigned long int time_now;

	time_now = get_the_time(NULL);
	while (get_the_time(NULL) < time_now + sleep_time)
		usleep(100);
}

int	can_philo_eat(t_data *philo, int num, int health)
{
	if (pthread_mutex_lock(philo->mu_eat) != 0)
		return (MUTEX_LOCK_ERROR);
	if (*philo->state != ALIVE)
		return (FAILURE);
	if (num == CAN_I_EAT_CHECK)
	{
		philo->time_eaten = get_the_time(NULL);
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

int		philo_go_eat(t_data *philo)
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
	if (*philo->state != ALIVE || can_philo_eat(philo, CAN_I_EAT_CHECK, 0) != SUCCESS) // Check if not dead before eating
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (FAILURE);
	}
	if (print_function(EATING, philo))
		return (PRINT_ERROR);
	sleeping(philo->time_to_eat);
	if (pthread_mutex_unlock(philo->right_fork) != 0 || (pthread_mutex_unlock(philo->left_fork) != 0))
		return (print_function(MUTEX_UNLOCK_ERROR, NULL));
	return (SUCCESS);
}


int	philo_go_sleep(t_data *philo)
{
	if (print_function(SLEEPING, philo))
		return (PRINT_ERROR);
	sleeping(philo->time_to_sleep);
	return (SUCCESS);
}

void*	start_loop(void *philo_void)
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
//This function checks the state of each philosopher 
void*	check_state(void *philo_s_void)
{
	t_data	*philo_s;
	int 	i;

	philo_s = philo_s_void;
	i = 0;
	while (1) // When works change to philo_s[i]->state != DEAD
	{
		if (i == philo_s->total_p)
			i = 0;
		if (can_philo_eat(&philo_s[i], 0, 0) != ALIVE && philo_s[i].eat_count != philo_s[i].eat_max)
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

//Creates a thread for every philosopher + 1 oversight thread that checks if a philosopher has died
void	start_pthreads(t_data *philo_s, pthread_t *philo_thread, int i)
{
	while (i < philo_s->total_p)
	{
		if (pthread_create(&philo_thread[i], NULL, start_loop, &philo_s[i])) // Philosopher threads
			return;
		sleeping(1);
		i++;
	}
	if (pthread_create(&philo_thread[i], NULL, check_state, philo_s))
		return;
	while (i >= 0)
	{
		pthread_join(philo_thread[i], NULL); // Waits for the thread specified by thread to terminate
		i--;
	}
}

int	main(int argc, char **argv)
{
	t_data		*philo_s;
	pthread_t	*philo_thread; 
	
	if (argc != 5 && argc != 6)
		return(printf("Error: invalid arguments\n"));
	else
	{
		if (parser(argc, argv))
			return (printf("Error input\n"));
		philo_s = malloc(sizeof(t_data) * ft_atoi(argv[1]));
		if (!philo_s)
			return (printf("malloc fail struct main\n"));
		if (initialize_struct(argc, argv, philo_s, 0))
			return (printf("initialize fail\n"));
		if (initialize_mutex(philo_s, 0))
		{
			// Free struct that has been initialized
			return (printf("Initialize mutex error\n"));
		}
		philo_thread = malloc(sizeof(pthread_t) * (philo_s->total_p + 1));
		if (!philo_thread)
		{
			printf("Pthread malloc fail\n");
			// Free struct that has been initialized
			// Free Mutex that has been initialized
		}
		start_pthreads(philo_s, philo_thread, 0);
		// free_function(); // Voor morgen
	}
	return (0);
}