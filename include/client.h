/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:53:52 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/09 19:17:00 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

extern volatile sig_atomic_t	g_sig_pid;

void	signal_handler(int signum, siginfo_t *info, void *dummy);
void	usage(void);
void	send_error(char *mes, int err);
int		end_com(int pid);

#endif
