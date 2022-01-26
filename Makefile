NAME		=	minishell
# BONUS		=	minishell_bonus

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
L_FLAGS		= 	-lreadline -L $(HOME)/.brew/opt/readline/lib
C_FLAG		=	-I $(HOME)/.brew/opt/readline/include

SRC_DIR		=	./src/
OBJ_DIR		=	./obj/
BONUS_DIR	=	./src/bonus/
BONUS_ODIR	=	./obj/bonus/

SRC_LIST	=	main.c	\
				input_parsing.c	\
				builtin_init.c	env_init.c env_lst_utils.c \
				utils.c	\
				cmd_splitter.c	cmd_utils.c \
				builtin_echo.c			\
				builtin_cd.c			\
				builtin_pwd.c			\
				builtin_env.c			\
				builtin_unset.c			\
				builtin_export.c		\
				get_env_var.c			\
				create_prompt.c			\
				utilities.c				\
				cmd_validity.c

# BONUS_LIST	=	minishell_bonus.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ			=	$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_LIST)))
# BONUS_SRC	=	$(addprefix $(BONUS_DIR), $(BONUS_LIST))
# BONUS_OBJ	=	$(addprefix $(BONUS_ODIR), $(patsubst %.c, %.o, $(BONUS_LIST)))

INCLUDES	=	./header/minishell.h
# B_INCLUDES	=	./header/minishell_bonus.h

LIBFT		=	./lib/libft/

# **************************************************************************** #
#									COLOURS									   #
# **************************************************************************** #

GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m

# **************************************************************************** #
#									RULES									   #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT) $(INCLUDES)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a -o $@ $(L_FLAGS)
	@echo "$(GREEN)creating: $(NAME)$(NC)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@echo "$(GREEN)creating: object-files: $(NC)\c"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(C_FLAG) $^ -c -o $@
	@echo "$(GREEN)>$(NC)\c"

# bonus: $(BONUS_ODIR) $(BONUS_OBJ) $(LIBFT) $(B_INCLUDES)
# 	@make -C $(LIBFT)
# 	@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT)/libft.a -o $(BONUS)
# 	@echo "$(GREEN)creating: $(BONUS)$(NC)"

# $(BONUS_ODIR):
# 	@mkdir -p $(OBJ_DIR)
# 	@mkdir $(BONUS_ODIR)
# 	@echo "$(GREEN)creating: bonus object-files: $(NC)\c"

# $(BONUS_ODIR)%.o: $(BONUS_DIR)%.c
# 	@$(CC) $(CFLAGS) $^ -c -o $@
# 	@echo "$(GREEN)>$(NC)\c"

clean:
	@rm -rf $(OBJ)
	@rm -rf -d $(OBJ_DIR)
	@make -C $(LIBFT) clean
	@echo "$(RED)deleting: object-files$(NC)"

fclean: clean
	@rm -rf $(NAME)
	# @rm -rf $(BONUS)
	@make -C $(LIBFT) fclean
	@echo "$(RED)deleting: $(NAME)$(NC)"
	# @echo "$(RED)deleting: $(BONUS)$(NC)"

re: fclean all

.PHONY: all bonus clean fclean re