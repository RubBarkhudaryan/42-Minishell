NAME	=	built_in

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3

SRCS	=	main.c \
			pwd.c\
			echo.c \
			cd.c \
			../parsing_env/env_parser.c #for testing cd and pwd
			../parsing_env/env_utils.c  

OBJS	=	$(SRCS:%.c=%.o)

LIBFT_DIR	=	../libft
LIBFT_A		=	$(LIBFT_DIR)/libft.a

PARS_ENV = ../parsing_env

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
