/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:52:20 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/01/14 20:09:02 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_count;

void	ft_handler(int n, siginfo_t *client_info, void *x)
{
	static char		c = 0;
	static pid_t	pid_c;

	(void) x;
	if (pid_c != client_info->si_pid && pid_c != 0)
	{
		c = 0;
		g_count = 0;
	}
	if (n == SIGUSR2)
		c = (1 << g_count) | c;
	g_count++;
	if (g_count == 8)
	{
		write(1, &c, 1);
		g_count = 0;
		c = 0;
	}
	pid_c = client_info->si_pid;
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = ft_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	pid = getpid();
	g_count = 0;
	ft_printf("PID : %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}
