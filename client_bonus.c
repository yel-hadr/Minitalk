/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:07:06 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/01/14 20:08:29 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_count;

void	ft_reply_message(int i)
{
	if (i == SIGUSR1)
		g_count++;
}

int	ft_send_bit(char c, int pid)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (i++ != 8 && n != -1)
	{
		if (c & 0x01)
			n = kill(pid, SIGUSR2);
		else
			n = kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(120);
		signal(SIGUSR1, ft_reply_message);
	}
	return (n);
}

int	ft_send(char *str, int pid)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (*str && n != -1)
	{
		n = ft_send_bit(*str, pid);
		if (g_count != ++i)
		{
			ft_printf("APAH APAH, SIGNAL MSHA APAH APAH\n");
			exit(0);
		}
		str++;
	}
	if (n == -1)
		ft_printf("Oopes, something has gone wroug !!\n");
	else if (g_count == i)
	{
		ft_printf("\n---the messages are sent successfully---\n");
		ft_printf("---contains : %d byte \n", g_count);
	}
	else
		ft_printf("Oopes, something has gone wroug !!\n");
	return (i);
}

int	main(int ac, char **av)
{
	int	pid;

	g_count = 0;
	pid = 0;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (!pid)
			ft_printf("Oopes, something has gone wroug !! \n");
		ft_send(av[2], pid);
	}
	else
	{
		ft_printf("Oopes, something has gone wroug !! \n");
	}
	return (0);
}
