NAME		=	minishell

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

# Flags when readline is in goinfre installed
L_FLAGS		=	-lreadline -L /goinfre/$(USER)/.brew/opt/readline/lib
C_FLAG		=	-I /goinfre/$(USER)/.brew/opt/readline/include

# //Kathi's brew Ordner <3
# L_FLAGS		=	-lreadline -L //Users/katharinahammerschmidt/.brew/opt/readline/lib
# C_FLAG		=	-I //Users/katharinahammerschmidt/.brew/opt/readline/include

# Mio's brew Ordner <3
# L_FLAGS			= -L/usr/local/opt/readline/lib -lreadline
# C_FLAG			= -I/usr/local/opt/readline/include

SRC_DIR		=	./src/
OBJ_DIR		=	./obj/
BONUS_DIR	=	./src/bonus/
BONUS_ODIR	=	./obj/bonus/

SRC_LIST	=	builtin_cd.c				\
				builtin_echo.c				\
				builtin_env.c				\
				builtin_exit.c				\
				builtin_export.c			\
				builtin_export_abc.c		\
				builtin_init.c 				\
				builtin_pwd.c				\
				builtin_unset.c				\
				builtin_utils.c				\
				cmd_dollar_expansion.c		\
				cmd_dollar_expand_utils_1.c	\
				cmd_dollar_expand_utils_2.c	\
				cmd_get_paths.c				\
				cmd_hdoc_dollar_expansion.c	\
				cmd_info.c					\
				cmd_lexer_parser.c			\
				cmd_lst_utils.c				\
				cmd_pipes.c					\
				cmd_qhandling.c				\
				cmd_redirection_input.c		\
				cmd_redirection_output.c	\
				cmd_redirections.c			\
				cmd_split_quotes_1.c		\
				cmd_split_quotes_2.c		\
				cmd_syntax_check.c			\
				cmd_table_creation.c		\
				env_get_env_var.c			\
				env_init.c					\
				env_handling.c				\
				env_lst_utils.c				\
				exec_builtin_parent.c		\
				exec_builtin.c				\
				exec_cmd_utils.c			\
				exec_cmd.c					\
				exec_here_doc_1.c			\
				exec_here_doc_2.c			\
				exec_process_loop.c			\
				exec_processes.c			\
				signals.c					\
				start_create_prompt.c		\
				start_main.c				\
				start_readline.c			\
				utils_free_memory.c			\
				utils_reset.c				\
				utils_str_mngt.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ			=	$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_LIST)))

INCLUDES	=	./header/minishell.h

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

clean:
	@rm -rf $(OBJ)
	@rm -rf -d $(OBJ_DIR)
	@make -C $(LIBFT) clean
	@echo "$(RED)deleting: object-files$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean
	@echo "$(RED)deleting: $(NAME)$(NC)"

re: fclean all

.PHONY: all bonus clean fclean re