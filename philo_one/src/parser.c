/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 12:05:02 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/10 17:59:14 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	parser(int argc, char **argv)
{
	int	i;
	int	y;

	i = 1;
	y = 0;
	while (i < argc)
	{
		y = 0;
		while (argv[i][y] != '\0')
		{
			if (!ft_is_digit(argv[i][y]))
				return (1);
			y++;
		}
		i++;
	}
	return (0);
}
