NAME = ft_printf.a
SRCS = ft_printf.c ft_putchar.c ft_putstr.c ft_putptr.c \
	ft_putnbr.c ft_putnbr_unsigned.c ft_putnbr_hex_down.c \
	ft_putnbr_hex_upper.c

all: $(NAME)

$(NAME):
	cc -Wall -Wextra -Werror -Ilibft -c $(SRCS)
	ar rcs $(NAME) *.o

clean: 
	rm -f *.o

fclean: clean
	rm -f ./includes/*.gch
	rm -f $(NAME)

re: fclean all