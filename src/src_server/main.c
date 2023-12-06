/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:23:03 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/06 20:43:59 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "libft.h"
#include "ft_printf.h"

static int	write_receive_data(void);
static void	send_error(char *mes);
static char	restore_char();

int	main(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	g_char_s = 0;
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
	if (write_receive_data())
		send_error("Error\n");
	exit(1);
}

int	write_receive_data(void)
{
	char	write_char;

	while (1)
	{
		pause();
		g_char_s = 0;
		while (!(g_char_s & IS_ERROR))
		{
			write_char = restore_char();
			if (write_char == 0)
				g_char_s |= IS_ERROR;
			if (!(g_char_s & IS_ERROR))
				write (STDOUT_FILENO, &write_char, 1);
		}
		if (g_char_s & IS_ERROR)
			send_error("Connection has been lost\n");
	}
	return (1);
}

static void	send_error(char *mes)
{
	while (*mes)
	{
		write (STDERR_FILENO, mes, 1);
		mes++;
	}
}

static char	restore_char()
{
	int		digit;
	int		usecond;
	char	re;


	digit = 0;
	re = 0;
	while ((digit < 7) && !(g_char_s & IS_ERROR))
	{
		printf("tst\n");
		g_char_s &= ~RECEIVE_CHAR;
		re += g_char_s & CHAR_BIT_IS;
		re = re << 1;
		usecond = 0;
		while ((usecond++ < 3000000) || (g_char_s & RECEIVE_CHAR))
			usleep(1);
		if (usecond >= 3000000)
			g_char_s |= IS_ERROR;
		digit++;
	}
	if (g_char_s & IS_ERROR)
		re = 0;
	return (re);
}
