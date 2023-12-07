/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:38:48 by rmakabe           #+#    #+#             */
/*   Updated: 2023/12/07 10:35:16 by rmakabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// D = during
#define IS_ERROR 0x80
#define RECEIVE_CHAR 0x40
#define CHAR_BIT_IS 0x01

extern volatile sig_atomic_t	g_char_s;

void	signal_handler(int signum, siginfo_t *info, void *dummy);

#endif
