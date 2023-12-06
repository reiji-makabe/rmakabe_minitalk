# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/11 21:23:55 by rmakabe           #+#    #+#              #
#    Updated: 2023/12/03 16:15:21 by rmakabe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTPRINTF := libftprintf/

ifdef WITH_DEBUG
	DEBUG :=-O0 -g3
endif

all:
	make -C $(LIBFTPRINTF)

clean:
	make clean -C $(LIBFTPRINTF)

fclean: clean
	make fclean -C $(LIBFTPRINTF)

re: fclean all

debug:
	make WITH_DEBUG=1 -C $(LIBFTPRINTF)

norm:
	make norm -C $(LIBFTPRINTF)

.PHONY: all clean fclean re debug norm
