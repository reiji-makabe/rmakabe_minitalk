/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:23:29 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/12 20:29:31 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	signal_handler(int signum, siginfo_t *info, void *dummy)
{
	static int	i = -1;
	char		c;

	g_char_s = g_char_s << 1;
	if (i < 0)
		i = 7;
	if (signum == SIGUSR1)
		g_char_s |= 1;
	else if (signum == SIGUSR2)
		g_char_s |= 0;
	i--;
	if (i < 0 && (g_char_s != 0xff))
	{
		c = g_char_s;
		write (STDOUT_FILENO, &c, 1);
		g_char_s = 0;
	}
	kill (info->si_pid, SIGUSR1);
	(void)dummy;
}
