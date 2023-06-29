# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 19:42:32 by ikaismou          #+#    #+#              #
#    Updated: 2023/06/29 11:43:05 by ikaismou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#CC = gcc
#
#SRCS = src/main.c src/parsing/parsing.c src/parsing/param.c src/utils/list.c src/parsing/map.c
#
#OBJS = $(SRCS:.c=.o)
#
#FLAGS = -Wall -Wextra -Werror
#
#NAME = cub3d
#
#HEAD = includes/cun3d.h
#
#RM = rm -f
#
#%.o: %.c Makefile ${HEAD}
#		${CC} ${FLAGS} -I libft -I/usr/include -Imlx_linux -O3 -c $< -o $@
#
#all:
#	make -C libft
#	make -C mlx_linux
#	make ${NAME}
#
#$(NAME): $(OBJS) libft/libft.a
#	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz libft/libft.a -o $(NAME) -lreadline
#
#clean:
#	${MAKE} clean -C libft/
#
#libft:
#	${MAKE} -C libft
#
#fclean: clean
#	${MAKE} fclean -C libft/
#	$(RM) $(OBJS)
#	$(RM) $(NAME)
#
#re: fclean
#	make all
#
#.PHONY:	all clean fclean re bonus libft


NAME		=	cub3d

INC			=	cub3d.h

INC_DIR		=	./includes/

HEADERS		= $(addprefix $(INC_DIR), $(INC))

SRC_DIR		=	./src/
SRC			=	main.c \
				parsing/parsing.c \
				parsing/param.c \
				utils/list.c \
				parsing/map.c


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
		$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT_A) -o $@ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lreadline

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