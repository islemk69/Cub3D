# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blakehal <blakehal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 19:42:32 by ikaismou          #+#    #+#              #
#    Updated: 2023/10/15 18:08:38 by blakehal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

INC			=	cub3d.h

INC_DIR		=	./includes/

HEADERS		= $(addprefix $(INC_DIR), $(INC))

SRC_DIR		=	./src/
SRC			=	main.c \
				parsing/parsing.c \
				parsing/param.c \
				parsing/map.c \
				parsing/check_file.c \
				utils/parsing_utils.c \
				utils/list.c \
				utils/init_struct.c \
				utils/drawsquare_utils.c \
				utils/free.c \
				game/init_game.c \
				game/movements.c \
				game/drawmap.c \
				game/scene.c \
				game/raycast.c \
				game/raycast_horizontal.c \
				game/raycast_vertical.c \
				game/key_management.c

LIBFT_DIR	=	libft/
LIBFT_A		=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	libft

OBJ_DIR		=	.objs/
OBJ			=	$(SRC:%.c=$(OBJ_DIR)%.o)

CC			=	cc
CC_FLAGS	=	-Wextra -Werror -Wall -g3 -O3

all:
	make -C libft
	make -C mlx_linux
	make ${NAME}

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) $(LIBFT_A) $(LIBFT_DIR)libft.h
		mkdir -p $(@D)
		$(CC) $(CC_FLAGS) -I$(INC_DIR) -I$(LIBFT_INC) -I/usr/include -Imlx_linux -c $< -o $@

$(NAME): $(OBJ)
		$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT_A) -o $@ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm 

${LIBFT_A}: FORCE
	$(MAKE) -C ${LIBFT_DIR}

FORCE:

build_libft: $(LIBFT_DIR)
		$(MAKE) -C $(LIBFT_DIR)

clean:
		$(MAKE) -C libft fclean
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re build_libft