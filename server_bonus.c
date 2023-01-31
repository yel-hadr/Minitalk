/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:06:13 by yel-hadr          #+#    #+#             */
/*   Updated: 2023/01/20 04:41:47 by yel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_count;

int	ft_unicode_len(char chr)
{
	int	n;
	int	itr;

	n = 0;
	itr = 7;
	while (((chr >> itr--) & 1) && n < 7)
		n++;
	return (n);
}

void	ft_unicode(char c, int reset)
{
	static int	len = 0;
	static char	*ptr = 0;
	static int	i = 0;

	if (reset || ft_unicode_len(c) > 1)
	{
		len = ft_unicode_len(c);
		if (ptr)
			free(ptr);
		ptr = NULL;
		ptr = ft_calloc(len, 1);
		i = 0;
	}
	ptr[i++] = c;
	if (i == len)
	{
		write(1, ptr, len);
		free(ptr);
		ptr = NULL;
		len = 0;
	}
}

void	ft_print_char(char c, int reset_uni)
{
	if (c < 0)
	{
		ft_unicode(c, reset_uni);
		reset_uni = 0;
	}
	else
		write(1, &c, 1);
}

void	ft_handler(int n, siginfo_t *client_info, void *x )
{
	static char		c = 0;
	static pid_t	pid_c;
	static int		reset_uni;

	(void) x;
	reset_uni = 0;
	if (pid_c != client_info->si_pid)
	{
		c = 0;
		g_count = 0;
		reset_uni = 1;
	}
	if (n == SIGUSR2)
		c = ((1 << g_count) | c);
	g_count++;
	if (g_count == 8)
	{
		ft_print_char(c, reset_uni);
		g_count = 0;
		c = 0;
		kill(pid_c, SIGUSR1);
	}
	pid_c = client_info->si_pid;
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	g_count = 0;
	sa.sa_sigaction = ft_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	pid = getpid();
	ft_printf("PID : %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}
