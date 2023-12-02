# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 12:33:03 by rmakabe           #+#    #+#              #
#    Updated: 2023/12/02 00:57:50 by rmakabe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT := client.a
SERVER := server.a
CC := cc
SANITIZE :=-fsanitize=leak -fsanitize=address

ifdef WITH_DEBUG
	DEBUG :=-O0 -g3
endif

RM := rm -rf
AR := ar -rcs

INCLUDE := include/
SRC_DIR := src/
SRC_DIR_SER := src/src_server/
SRC_DIR_CLI := src/src_client/
OBJ_DIR := obj/
OBJ_DIR_SER := obj/obj_server/
OBJ_DIR_CLI := obj/obj_client/

CFLAGS := -Wall -Wextra -Werror $(DEBUG) $(SANITIZE) -I

SRC_SER := $(wildcard $(SRC_DIR_SER)*.c)
SRC_CLI := $(wildcard $(SRC_DIR_CLI)*.c)
OBJ_SER := $(addprefix $(OBJ_DIR_SER), $(notdir $(SRC_SER:.c=.o)))
OBJ_CLI := $(addprefix $(OBJ_DIR_CLI), $(notdir $(SRC_CLI:.c=.o)))


#command
all: $(CLIENT) $(SERVER)

$(CLIENT):$(OBJ_CLI)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $(NAME)

$(OBJ_DIR_CLI)%.o:$(SRC_DIR_CLI)%.c
	@mkdir -p $(OBJ_DIR_CLI)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

$(SERVER):$(OBJ_SER)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $(NAME)

$(OBJ_DIR_SER)%.o:$(SRC_DIR_SER)%.c
	@mkdir -p $(OBJ_DIR_SER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(NAME) $(SERVER) $(CLIENT)

re: fclean all

debug:
	make WITH_DEBUG=1 re -C $(FILE)

norm:
	@norminette $(SRC_DIR) $(INCLUDE) | grep Error true

.PHONY: all clean fclean re debug norm