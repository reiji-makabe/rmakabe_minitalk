/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:07:17 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/01 12:26:08 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	signal_handler(int signum, siginfo_t *info, void *dummy)
{
	if (signum == SIGUSR1)
		sig_pid == info->si_pid;
	else
		sig_pid == 0;
}
