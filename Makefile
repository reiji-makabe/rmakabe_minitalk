# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakabe <rmkabe012@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 12:33:03 by rmakabe           #+#    #+#              #
#    Updated: 2023/12/07 10:25:24 by rmakabe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME is neccesarry!
CLIENT := client
SERVER := server
CC := gcc
SANITIZE :=-fsanitize=address

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
#CFLAGS :=$(DEBUG) $(SANITIZE) -I

SRC_SER := $(wildcard $(SRC_DIR_SER)*.c)
SRC_CLI := $(wildcard $(SRC_DIR_CLI)*.c)
OBJ_SER := $(addprefix $(OBJ_DIR_SER), $(notdir $(SRC_SER:.c=.o)))
OBJ_CLI := $(addprefix $(OBJ_DIR_CLI), $(notdir $(SRC_CLI:.c=.o)))

ARCHIVE_DIR := archive/
LIB_DIR := 42_library/

LIB := $(filter-out $(LIB_DIR)Makefile, $(wildcard $(LIB_DIR)*))
ARCHIVE := $(addsuffix .a, $(subst $(LIB_DIR), $(ARCHIVE_DIR), $(LIB)))


#command

all:$(CLIENT) $(SERVER)

$(CLIENT):$(OBJ_CLI)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $(CLIENT) $(ARCHIVE)

$(OBJ_DIR_CLI)%.o:$(SRC_DIR_CLI)%.c
	@mkdir -p $(ARCHIVE_DIR)
	make -C $(LIB_DIR)
	@mkdir -p $(OBJ_DIR_CLI)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

$(SERVER):$(OBJ_SER)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $(SERVER) $(ARCHIVE)

$(OBJ_DIR_SER)%.o:$(SRC_DIR_SER)%.c
	@mkdir -p $(ARCHIVE_DIR)
	make -C $(LIB_DIR)
	@mkdir -p $(OBJ_DIR_SER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

$(ARCHIVE):
	@mkdir -p $(ARCHIVE_DIR)
ifdef WITH_DEBUG
	make debug -C $(LIB_DIR)
else
	make -C $(LIB_DIR)
endif

clean:
	$(RM) $(OBJ_CLI) $(OBJ_SER) $(ARCHIVE)
	make clean -C $(LIB_DIR)

fclean: clean
	$(RM) $(NAME) $(SERVER) $(CLIENT)
	make fclean -C $(LIB_DIR)

re: fclean all

debug:
	make WITH_DEBUG=1 re -C $(FILE)

norm:
	@norminette $(SRC_DIR) $(INCLUDE) | grep Error true

.PHONY: all clean fclean re debug norm
