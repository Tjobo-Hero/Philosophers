/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 11:11:49 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/15 18:19:28 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	print_function(int num, t_data *philo)
{
	if (sem_wait(philo->sem_write) == -1)
		return (printf("Error: sem_wait fail\n"));
	if (num == SEM_WAIT_ERROR)
		return (printf("Error: sem_wait fail\n"));
	else if (num == SEM_POST_ERROR)
		return (printf("Error: sem_post fail\n"));
	else if (num == SLEEPING)
		printf("%lu-philo:[%i] is sleeping\n", get_time(philo), philo->p_nb);
	else if (num == LEFT_FORK)
		printf("%lu-philo:[%i] takes L fork\n", get_time(philo), philo->p_nb);
	else if (num == RIGHT_FORK)
		printf("%lu-philo:[%i] takes R fork\n", get_time(philo), philo->p_nb);
	else if (num == EATING)
		printf("%lu-philo:[%i] is eating\n", get_time(philo), philo->p_nb);
	else if (num == THINKING)
		printf("%lu-philo:[%i] is thinking\n", get_time(philo), philo->p_nb);
	else if (num == DEAD)
		printf("%lu-philo:[%i] died\n", get_time(philo), philo->p_nb);
	if (sem_post(philo->sem_write) == -1)
		return (printf("Error: sem_post fail\n"));
	return (0);
}

unsigned long int	get_time(t_data *philo)
{
	struct timeval		current_time;
	unsigned long int	time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	if (philo == NULL)
		return (time);
	else
		return (time - philo->time_created);
}

static long int	ft_convert(const char *str, int i,
unsigned long int result, int sign)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((result >= 922337203685477580 && (str[i] - '0') > 7) && sign == 1)
			return (-1);
		else if ((result >= 922337203685477580 && (str[i] - '0') > 8)
			&& sign == -1)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	unsigned long int	result;
	int					i;
	int					sign;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == ' ' || (8 < str[i] && str[i] < 14)))
		i++;
	if ((str[i] == '+' && str[i + 1] == '-')
		|| (str[i] == '-' && str[i + 1] == '+'))
		return (0);
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
		if (str[i] == '+')
			return (0);
	}
	result = ft_convert(str, i, result, sign);
	return ((int)result * sign);
}

int	dead_or_alive(t_data *philo)
{
	if (get_time(NULL) >= philo->time_eaten + philo->time_to_die)
	{
		print_function(DEAD, philo);
		if (sem_post(philo->sem_state) == -1)
			exit(1);
		return (DEAD);
	}
	else
		return (ALIVE);
}
