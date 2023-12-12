/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:07:17 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/13 00:14:17 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	signal_handler(int signum, siginfo_t *info, void *dummy)
{
	static int	id = 0;

	if (info->si_pid != 0)
		id = info->si_pid;
	if (signum == SIGUSR1)
		g_sig_pid = id;
	else
		g_sig_pid = 0;
	(void)dummy;
}
