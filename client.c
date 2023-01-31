/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:08:07 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/01/28 00:35:31 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minitalk.h"

void	ft_send_bit(char c, int pid)
{
	int	i;

	i = 0;
	while (i++ != 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(80);
	}
}

void	ft_send(char *str, int pid)
{
	while (*str)
	{
		ft_send_bit(*str, pid);
		str++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		ft_send(av[2], ft_atoi(av[1]));
	}
	else
	{
		ft_printf("Oopes, something has gone wroug !! \n");
	}
	return (0);
}
