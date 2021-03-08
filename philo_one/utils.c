/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 11:11:49 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/08 11:39:33 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long int get_the_time(t_data *philo)
{
	struct timeval	current_time;
	gettimeofday(&current_time, NULL);

	unsigned long int time;

	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);  	// converting seconds to miliseconds
	// time += current_time.tv_usec / 1000; 	// converting microsecond to miliseconds

	if (philo == NULL)
		return (time);
	else
		return (time - philo->time_stamp);
}

int	print_function(int num, t_data *philo)
{
	if (num == 1)
		printf("%lu [%i] is sleeping\n", get_the_time(philo), philo->p_number);
	else if (num == 2)
		printf("%lu [%i] has taken a fork\n", get_the_time(philo), philo->p_number);
	else if (num == 3)
		printf("%lu [%i] is eating\n", get_the_time(philo), philo->p_number);
	else
		printf("thinking");
	return (0);
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

int				ft_atoi(const char *str)
{
	unsigned long int	result;
	int					i;
	int					sign;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == ' ' || (8 < str[i] && str[i] < 14)))
		i++;
	if ((str[i] == '+' && str[i + 1] == '-') ||
	(str[i] == '-' && str[i + 1] == '+'))
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
