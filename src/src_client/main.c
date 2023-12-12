/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:22:52 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/09 19:23:50 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft.h"

static int	check_pid_collect(char *pid);
static int	send_str(int pid, char *str);
static int	send_char(int pid, char c);

volatile sig_atomic_t	g_sig_pid = 0;

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	sa1;
	struct sigaction	sa2;

	if (argc != 3)
		usage();
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

static int	check_pid_collect(char *pid)
{
	int		re;
	char	*tmp;

	re = ft_atoi(pid);
	tmp = ft_itoa(re);
	if (ft_strlen(tmp) != ft_strlen(pid)
		|| ft_strncmp(tmp, pid, ft_strlen(pid)))
		return (0);
	free (tmp);
	return (re);
}

static int	send_str(int pid, char *str)
{
	char	err;

	err = 0;
	while (*str && !err)
	{
		err = 0;
		err = send_char (pid, *str);
		if (err == 1)
			return (1);
		str++;
	}
	err = end_com(pid);
	return (0);
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
		g_sig_pid = 0;
		while (usecond++ < 30000 && (g_sig_pid == 0))
			usleep(100);
		if (g_sig_pid == pid)
			g_sig_pid = 0;
		else
			return (1);
	}
	return (0);
}

void	send_error(char *mes, int err)
{
	while (*mes)
	{
		write (STDERR_FILENO, mes, 1);
		mes++;
	}
	exit (err);
}
