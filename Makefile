NAME		= minishell
LIBFT		= libft.a
FT_PRINTF	= ft_printf.a
SRCS		= ./src/main.c ./src/functions_aux.c ./src/frees.c ./src/frees2.c\
		./src/tokens/tokens.c ./src/tokens/aux_tokens.c ./src/tokens/aux2_tokens.c ./src/tokens/aux3_tokens.c\
		./src/built-ins/echo.c ./src/built-ins/cd.c ./src/built-ins/pwd.c ./src/built-ins/envs_init.c \
		./src/built-ins/env.c ./src/built-ins/exit.c ./src/built-ins/unset.c ./src/built-ins/export.c\
		./src/exec/exec_patch.c ./src/exec/exec.c
OBJC		= $(patsubst ./src/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJ_DIR		= obj
CC			= cc
CFLAGS		= -g3 -Wall -Werror -Wextra
RL_FLAGS	= -lreadline -lhistory
INCLUDE		= -I include
RM			= rm -rf
SRC_TESTE	= mini_expand.c

all: $(NAME)

$(NAME) : $(OBJC)
	@make -C libs/libft
	@make -C libs/ft_printf
	$(CC) $(CFLAGS) $(OBJC) $(INCLUDE) libs/ft_printf/$(FT_PRINTF) libs/libft/$(LIBFT) $(RL_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@make clean -C libs/libft
	@make clean -C libs/ft_printf
	${RM} ${OBJC}

fclean: clean
	@make fclean -C libs/libft
	@make fclean -C libs/ft_printf
	${RM} ${NAME}

re: fclean all

teste:
	@make -C libs/libft
	@make -C libs/ft_printf
	$(CC) $(CFLAGS) $(SRC_TESTE) $(INCLUDE) libs/ft_printf/$(FT_PRINTF) libs/libft/$(LIBFT) $(RL_FLAGS) -o teste

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		valgrind --suppressions=valgrind.supp --leak-check=full --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all clean fclean re val teste