/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 10:28:51 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/04 16:22:17 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct			s_data
{
	int					total_p;
	int					p_number;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_max;
	int					eat_count;
	unsigned long int	time_stamp;
	unsigned long int	time_created;
}						t_data;


/* UTILS */
int						ft_atoi(const char *str);
unsigned long int 		get_the_time(t_data *philo);

#endif
