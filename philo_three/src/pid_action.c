/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pid_action.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 13:53:56 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/16 12:24:50 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include "string.h"

void	pid_action(t_data *philo_s, int i)
{
	while (i < philo_s->total_p)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}
