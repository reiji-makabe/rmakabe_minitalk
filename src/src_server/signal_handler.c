/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:23:29 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/13 01:01:39 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	signal_handler(int signum, siginfo_t *info, void *dummy)
{
	static int	i = -1;
	static char	c = 0;
	static int	id = 0;

	if (info->si_pid != 0)
		id = info->si_pid;
	if (i < 0)
		i = 7;
	if (signum == SIGUSR1)
		c |= (1 << i);
	i--;
	if (i < 0)
	{
		if (c == 0x04)
		{
			i = -1;
			c = 0;
			g_sig_pid_s = 1;
			return ;
		}
		write (STDOUT_FILENO, &c, 1);
		c = 0;
	}
	g_sig_pid_s = id;
	(void)dummy;
}
