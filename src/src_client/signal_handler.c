/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:07:17 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/07 17:51:33 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	signal_handler(int signum, siginfo_t *info, void *dummy)
{
	usleep(300);
	if (signum == SIGUSR1)
		g_sig_pid = info->si_pid;
	else
		g_sig_pid = 0;
	(void)dummy;
}
