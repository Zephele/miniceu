NAME		= minishell
LIBFT		= libft.a
FT_PRINTF	= ft_printf.a
SRCS		= ./src/main.c ./src/tokens.c ./src/frees.c 
OBJC		= $(patsubst ./src/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJ_DIR		= obj
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RL_FLAGS	= -lreadline -lncurses
INCLUDE		= -I include
RM			= rm -rf

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

.PHONY: all clean fclean re