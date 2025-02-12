# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 14:52:14 by axburin-          #+#    #+#              #
#    Updated: 2025/01/12 12:10:38 by axburin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBC =	ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha \
		ft_isascii ft_isdigit ft_isprint ft_memchr \
		ft_memcmp ft_memcpy ft_memmove ft_memset ft_strchr \
		ft_strdup ft_strlcat ft_strlcpy ft_strlen ft_strncmp \
		ft_strnstr ft_strrchr ft_tolower ft_toupper 

ADDITIONAL =	ft_itoa ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd \
				ft_split ft_strjoin ft_strmapi ft_strtrim ft_substr ft_striteri gnl/get_next_line

BONUS = ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus

SRCS = $(addsuffix .c, ${LIBC}${ADDITIONAL})
OBJS = $(addsuffix .o, ${LIBC}${ADDITIONAL})

OBJS_BONUS = $(addsuffix .o, ${BONUS})

all: ${NAME}

${NAME}: ${OBJS}
	@echo "✅ Compilation des fichiers sources"
	@ar -rcs ${NAME} ${OBJS}
	@echo "✅ Bibliothèque créée"

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	@rm -rf ${OBJS} ${OBJS_BONUS}
	@echo "✅ Suppression des fichiers sources"

fclean: clean
	@rm -rf ${NAME}
	@echo "✅ Suppression de la bibliothèque"

re: fclean all

bonus: ${OBJS_BONUS}
	@echo "✅ Compilation des fichiers bonus"
	@ar -rcs ${NAME} ${OBJS_BONUS}

.PHONY = all clean fclean re bonus
