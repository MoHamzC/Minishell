# Nom de la bibliothèque
NAME = libft.a

# Compilateur et options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

# Commandes pour créer et supprimer des fichiers
AR = ar rcs
RM = rm -f

# Liste des fichiers source
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strcmp.c

# Liste des fichiers source bonus
BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

# Liste des fichiers objets générés à partir des sources
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Cible par défaut
all: $(NAME)

# Règle pour créer la bibliothèque
$(NAME): $(OBJS)
	$(AR) $@ $^

# Règle pour compiler les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets
clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

# Règle pour nettoyer les fichiers objets et la bibliothèque
fclean: clean
	$(RM) $(NAME)

# Règle pour recompiler tout
re: fclean all

# Règle pour compiler les fichiers bonus
bonus: $(BONUS_OBJS)
	$(AR) $(NAME) $^

# Indique que ces cibles ne sont pas des fichiers
.PHONY: all clean fclean re _bonus