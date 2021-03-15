/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 12:06:03 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/03/15 17:24:23 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int 	main(int argc, char **argv)
{
	int pid1 = fork();
	if (pid1 == -1)
	{
		printf("Error creating process");
		return (1);
	}
	if (pid1 == 0)
	{
		sleep(4);
		printf("Finished execution (%d)\n", getpid());
		return (0);
	}
	int pid2 = fork();
	if (pid2 == -1)
	{
		printf("Error creating process");
		return (2);		
	}
	if (pid2 == 0)
	{
		sleep(2);
		printf("Finished execution (%d)\n", getpid());
		return (2);
	}
	int pid1_res = waitpid(pid1, NULL, 0);
	printf("Waited for %d\n", pid1_res);
	int pid2_res = wait(NULL);
	printf("Waited for %d\n", pid2_res);
	return (0);
}