/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:23:29 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/06 16:14:26 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	signal_handler(int signum, siginfo_t *info, void *dummy)
{
	g_char_s |= RECEIVE_CHAR;
	if (signum == SIGUSR1)
		g_char_s |= CHAR_BIT_IS;
	else if (signum == SIGUSR2)
		g_char_s &= ~CHAR_BIT_IS;
	kill (info->si_pid, SIGUSR1);
	dummy = NULL;
}
