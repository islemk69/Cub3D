# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 19:42:32 by ikaismou          #+#    #+#              #
#    Updated: 2023/06/20 14:13:31 by ikaismou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

SRCS = src/main.c src/parsing/parsing.c src/parsing/param.c src/utils/list.c
		
OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

NAME = cub3d

HEAD = includes/cun3d.h

RM = rm -f

%.o: %.c Makefile ${HEAD}
		${CC} ${FLAGS} -I libft -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: 
	make -C libft
	make -C mlx_linux
	make ${NAME}

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz libft/libft.a -o $(NAME) -lreadline

clean:
	${MAKE} clean -C libft/

libft:
	${MAKE} -C libft

fclean: clean
	${MAKE} fclean -C libft/
	$(RM) $(OBJS)
	$(RM) $(NAME)
	
re: fclean
	make all

.PHONY:	all clean fclean re bonus libft