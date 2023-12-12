/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:23:29 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/09 19:02:55 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	signal_handler(int signum, siginfo_t *info, void *dummy)
{
	static int	i = 0;
	char		c;

	g_char_s = g_char_s << 1;
	if (signum == SIGUSR1)
		g_char_s |= 1;
	else if (signum == SIGUSR2)
		g_char_s |= 0;
	i++;
	c = 0xff & g_char_s;
	if (i == 8 && (g_char_s != 0xff))
	{
		write (STDOUT_FILENO, &c, 1);
		g_char_s = 0;
		i = 0;
	}
	else if (g_char_s == 0xff)
		i = 0;
	kill (info->si_pid, SIGUSR1);
	(void)dummy;
}
