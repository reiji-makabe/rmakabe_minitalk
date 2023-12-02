/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:25:09 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/02 12:59:12 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int	check_pid_collect (char *pid);
static void	send_str (int pid, char *str);
static void	send_char (int pid, char *str);
static void	send_error(char *mes, int err);

volatile sig_atomic_t	sig_pid = 0;

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	sa1;
	struct sigaction	sa2;

	if (argc != 3)
		exit (1);
	pid = check_pid_collect(argv[1]);
	if (pid == 0)
		exit (1);
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
	if (send_str(pid, argv[2]))
		send_error("Server Error", 1);
}

static int	check_pid_collect (char *pid)
{
	int		re;
	char	*tmp;

	re = ft_atoi(pid);
	tmp = ft_itoa(re);
	if (ft_strlen(tmp) != ft_strlen(pid) || ft_strncmp(tmp, pid, ft_strlen(pid)))
			return (0);
	return (re);
}

static void	send_str(int pid, char *str)
{
	while (*str)
	{
		send_char (pid, *str);
		str++;
	}
}

static int	send_char(int pid, char c)
{
	int	digit;
	int	usecond;
	int	error;

	digit = 7;
	while (digit >= 0)
	{
		if (c & (1 << digit))
			error = kill (pid, SIGUSR1);
		else
			error = kill (pid, SIGUSR2);
		digit--;
		if (error != 0)
			send_error("pid is incollect or server not found\n", error);
		usecond = 0;
		while (usecond++ < 30000 || (sig_pid & IS_ERROR))
			usleep(100);
		if (sig_pid != 0 && sig_pid == pid)
			sig_pid = 0;
		else
			return (1);
	}
}

static void	send_error(char *mes, int err)
{
	while (*mes)
	{
		write (STDERR_FILENO, mes, 1);
		mes++;
	}
	exit (err);
}
