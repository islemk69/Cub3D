# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/13 14:15:27 by ikaismou          #+#    #+#              #
#    Updated: 2023/06/19 16:30:55 by ikaismou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
		ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
		ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
		ft_tolower.c ft_toupper.c ft_printf.c ft_printf_utils.c get_next_line.c \
		get_next_line_utils.c ft_free_tab.c ft_strlen_dtab.c

BONUSSRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
			ft_lstmap.c

OBJS = $(SRCS:.c=.o)

BONUSOBJS = $(BONUSSRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

HEAD = libft.h

CC = gcc

%o: %c Makefile ${HEAD}
		${CC} ${FLAGS} -I ${HEAD} -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(BONUSOBJS)
	ar rcs $(NAME) $(OBJS) $(BONUSOBJS)

clean:
	$(RM) $(OBJS) $(BONUSOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

bonus: $(NAME) $(BONUSOBJS)
	ar rcs $(NAME) $(OBJS) $(BONUSOBJS)

.PHONY:	all clean fclean re bonus
