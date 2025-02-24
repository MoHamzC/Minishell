MAKEFLAGS += -sj1

###############################################################################
#                                CONFIGURATION                                #
###############################################################################

# Compilateur et options de compilation
CC      := cc
CFLAGS  := -g3 -Wall -Wextra -Werror -Iinclude 

# Répertoires sources et objets
SRC_DIRS := ./src include/gnl
OBJ_DIR  := obj

# Fichiers sources et objets
SRC_WITHOUT_MAIN := $(shell find $(SRC_DIRS) -iname "*.c")

FUZZER_SRC := $(SRC_WITHOUT_MAIN) src/fuzzer.o
FUZZER_OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(FUZZER_SRC))

SRCS := main.c $(shell find $(SRC_DIRS) -iname "*.c")
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Bibliothèque externe (libft)
LIBFT := include/libft/libft.a
LIBS  := $(LIBFT)

# Nom de l'exécutable final
TARGET := minishell

# Outil de nettoyage
RM := rm -rf

# Couleurs pour l'affichage
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
RED     := \033[0;31m
BLUE    := \033[0;34m
PURPLE  := \033[0;35m
CYAN    := \033[0;36m
NC      := \033[0m

# Calcul du nombre total d'objets (pour la barre de progression)
TOTAL_OBJS := $(words $(OBJS))

###############################################################################
#                                RÈGLES MAKE                                  #
###############################################################################

# Note : Pour éviter les problèmes avec la barre de progression,
# exécutez make en mode séquentiel (make -j1).

# Cible par défaut
all: prepare_progress $(TARGET)

banner:
	@echo "$(CYAN)"
	@echo "============================================"
	@echo "    	"$(TARGET)" ready! Let's go!	 "
	@echo "============================================"
	@echo "$(NC)"

# Prépare le compteur de progression
prepare_progress:
	@echo 0 > .progress_counter

# Compilation des fichiers .c en .o avec mise à jour de la barre de progression
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo - "$(YELLOW)[COMPILATION]$(NC) $<"
	@$(CC) $(CFLAGS) -c $< -o $@
	@COUNT=$$(cat .progress_counter); \
	NEW_COUNT=$$((COUNT+1)); \
	ROW=$$(expr $$(tput lines) - 1); \
	tput cup $$ROW 0; \
	printf "\r\033[2K["; \
	echo $$NEW_COUNT > .progress_counter; \
	PERCENT=$$((NEW_COUNT*100/$(TOTAL_OBJS))); \
	BARS=$$((PERCENT/10)); \
	SPACES=$$((10 - BARS)); \
	for i in $$(seq 1 $$BARS); do printf "#"; done; \
	for i in $$(seq 1 $$SPACES); do printf " "; done; \
	printf "] %d%%" $$PERCENT; \
	if [ $$PERCENT -eq 100 ]; then echo ""; fi;

# Edition des liens et création de l'exécutable
$(TARGET): $(OBJS) $(LIBFT)
	@echo - "\n$(YELLOW)[LINKING]$(NC) Création de $(TARGET)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET) -lreadline
	@echo - "$(GREEN)[SUCCESS]$(NC) Exécutable $(TARGET) généré !"
	$(MAKE) banner

# Construction de libft
$(LIBFT):
	@echo - "$(YELLOW)[LIBFT]$(NC) Construction de la libft..."
	@$(MAKE) -C include/libft
	@echo - "$(GREEN)[LIBFT]$(NC) libft construite avec succès !"

# Nettoyage des fichiers objets et du compteur de progression
clean:
	@echo - "$(RED)[CLEAN]$(NC) Suppression des fichiers objets..."
	@$(RM) $(OBJ_DIR) .progress_counter
	@$(MAKE) -C include/libft clean
	@echo - "$(GREEN)[CLEAN]$(NC) Nettoyage terminé !"

# Nettoyage complet (objets, compteur et exécutable)
fclean: clean
	@echo - "$(RED)[FCLEAN]$(NC) Suppression de l'exécutable $(TARGET)..."
	@$(RM) $(TARGET)
	@$(MAKE) -C include/libft fclean
	@echo - "$(GREEN)[FCLEAN]$(NC) Nettoyage complet terminé !"

fuzzer: CFLAGS += -fsanitize=fuzzer,address
fuzzer: $(FUZZER_OBJS) $(LIBFT)
	clang -o $@ $(FUZZER_OBJS) $(LIBS) $(CFLAGS)

# Rebuild complet
re: fclean all

###############################################################################
#                                PHONY TARGETS                                #
###############################################################################
.PHONY: all prepare_progress clean fclean re
