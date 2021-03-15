/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pid_action.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 13:53:56 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/15 17:29:22 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	pid_action(t_data *philo_s, int i)
{
	// int status[philo_s->total_p];

	
	while (i < philo_s->total_p)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	// for (int i = 0; i < philo_s->total_p; i++)
	// 	printf("%i\n", status[i]);
}
