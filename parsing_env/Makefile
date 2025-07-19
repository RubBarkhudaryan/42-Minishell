NAME	=	pars_env

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3

SRCS	=	main.c \
			env_parser.c \
			env_utils.c \

OBJS	=	$(SRCS:%.c=%.o)

LIBFT_DIR	=	../libft
LIBFT_A		=	$(LIBFT_DIR)/libft.a

all: $(LIBFT_A) $(NAME)


$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)


$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean


fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
