CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -Iinclude
SRCS = main.c src/parsing/tokenization/tokenize.c src/parsing/tokenization/expand.c\
			src/env.c src/parsing/tokenization/post_tokenize.c src/parsing/tokenization/expand_complex.c\
			src/parsing/tokenization/utils.c src/parsing/tokenization/assign_token.c\
			src/parsing/tokenization/pre_redir.c
LIBS = include/libft/libft.a
TARGET = minishell

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

all: $(TARGET)

$(TARGET): $(SRCS) include/libft/libft.a
	@echo -e "$(YELLOW)Building $(TARGET)...$(NC)"
	$(CC) $(SRCS) $(LIBS) $(CFLAGS) -o $(TARGET)
	@echo -e "$(GREEN)Build complete!$(NC)"
	@echo -e "$(GREEN)Executable: $(TARGET)$(NC)"

include/libft/libft.a:
	@echo -e "$(YELLOW)Building libft...$(NC)"
	make -C include/libft
	@echo -e "$(GREEN)libft built successfully!$(NC)"

clean:
	@echo -e "$(RED)Cleaning up...$(NC)"
	rm -f $(TARGET)
	make -C include/libft clean
	@echo -e "$(GREEN)Clean complete!$(NC)"

fclean: clean
	@echo -e "$(RED)Full clean...$(NC)"
	rm -f $(TARGET)
	make -C include/libft fclean
	@echo -e "$(GREEN)Full clean complete!$(NC)"

re: fclean all

.PHONY: all clean fclean re