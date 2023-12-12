/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:23:03 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/13 01:03:45 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "libft.h"
#include "ft_printf.h"

static int	write_receive_data(void);

volatile sig_atomic_t	g_sig_pid_s = 0;

int	main(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	ft_printf("server pid is %d\n", getpid());
	memset(&sa1, 0, sizeof(sigaction));
	memset(&sa2, 0, sizeof(sigaction));
	sa1.sa_sigaction = signal_handler;
	sa2.sa_sigaction = signal_handler;
	sa1.sa_flags = SA_SIGINFO;
	sa2.sa_flags = SA_SIGINFO;
	sigaddset(&sa1.sa_mask, SIGUSR2);
	sigaddset(&sa2.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);
	while (1)
	{
		pause();
		if (write_receive_data())
			ft_printf("Error\n");
	}
	exit(1);
}

int	write_receive_data(void)
{
	int	loop;
	int	send;

	loop = 1;
	while (loop)
	{
		if (g_sig_pid_s == 1)
		{
			kill (send, SIGUSR1);
			loop = 0;
			break ;
		}
		usleep(30);
		send = g_sig_pid_s;
		kill (g_sig_pid_s, SIGUSR1);
		pause();
	}
	return (0);
}
