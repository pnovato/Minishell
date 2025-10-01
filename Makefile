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
list_utils/new_node.c \
3_built_ins/builtin_cd.c \
3_built_ins/builtin_pwd.c \
3_built_ins/builtin_echo.c \
3_built_ins/builtin_exit.c \
3_built_ins/handle_the_inputs.c


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

re: fclean all

.PHONY: all clean fclean re
