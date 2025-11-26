NAME = minishell
CC = cc
C_FLAGS = -Wall -Werror -Wextra -g
LIBFT_DIR = libft
SRC_DIR = ./source/
OBJ_DIR = ./objs/
LIBFT = $(LIBFT_DIR)/libft.a
SRC = main.c \
1_pre_expansion/env_to_list.c \
2_expansion/expand.c \
2_expansion/env_size.c \
list_utils/new_node.c \
3_built_ins/builtin_cd.c \
3_built_ins/builtin_pwd.c \
3_built_ins/builtin_echo.c \
3_built_ins/builtin_exit.c \
3_built_ins/builtin_env.c \
3_built_ins/builtins_export.c \
3_built_ins/builtins_unset.c \
3_built_ins/remove_env_var.c \
3_built_ins/update_env_value.c \
3_built_ins/handle_the_inputs.c \
4_tokenization/line_to_token.c \
4_tokenization/token_aux.c \
5_parsing/ast.c \
5_parsing/token_ast_aux.c \
6_execution/env_to_array.c \
6_execution/is_builtin.c \
6_execution/join_path.c \
6_execution/join_key_value.c \
6_execution/resolve_path.c \
6_execution/exec_ast_pipe.c \
6_execution/exec_ast_redirect.c \
6_execution/exec_ast_heredoc.c \
6_execution/exec_ast.c \
_checker/bool_checker.c \
_checker/node_type_checker.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@echo "building Minishell..."
	@$(CC) $(C_FLAGS) -I$(LIBFT_DIR) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

	@echo "Minishell ready!"

# > /dev/null redireciona o stdout, e nao mostra nada 
# 2>&1 redireciona os stderr tbm

clean:
	@echo "Executing cleaning..."
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@echo "Cleaned!"

fclean: clean
	@echo "Executing full cleaning..."
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) fclean
	@echo "Full cleaning done!"

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

re: fclean all

.PHONY: all clean fclean re
