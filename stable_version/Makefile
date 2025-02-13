CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -Iinclude
SRCS    := main.c $(shell find ./src ./include/gnl -iname "*.c") 
OBJ_DIR := obj
OBJS    := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
LIBS = include/libft/libft.a
TARGET = minishell

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

all: $(TARGET)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJS) include/libft/libft.a
	@echo -e "$(YELLOW)Building $(TARGET)...$(NC)"
	$(CC) $(OBJS) $(LIBS) $(CFLAGS) -o $(TARGET)
	@echo -e "$(GREEN)Build complete!$(NC)"
	@echo -e "$(GREEN)Executable: $(TARGET)$(NC)"

include/libft/libft.a:
	@echo -e "$(YELLOW)Building libft...$(NC)"
	make -C include/libft
	@echo -e "$(GREEN)libft built successfully!$(NC)"

clean:
	@echo -e "$(RED)Cleaning up...$(NC)"
	rm -rf $(OBJ_DIR)
	make -C include/libft clean
	@echo -e "$(GREEN)Clean complete!$(NC)"

fclean: clean
	@echo -e "$(RED)Full clean...$(NC)"
	rm -f $(TARGET)
	make -C include/libft fclean
	@echo -e "$(GREEN)Full clean complete!$(NC)"

re: fclean all

.PHONY: all clean fclean re
