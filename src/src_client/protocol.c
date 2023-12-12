/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:34:47 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/12 23:09:15 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	end_com(int pid)
{
	int	i;
	int	err;
	int	usecond;

	i = 0;
	while (i++ < 8)
	{
		if (i == 6)
			err = kill (pid, SIGUSR1);
		else
			err = kill (pid, SIGUSR2);
		if (err != 0)
			send_error("pid is incollect or server not found\n", err);
		usecond = 0;
		g_sig_pid = 0;
		while (usecond++ < 30000 && (g_sig_pid == 0))
			usleep (100);
		if (g_sig_pid == pid)
			g_sig_pid = 0;
		else
			return (1);
	}
	return (0);
}
