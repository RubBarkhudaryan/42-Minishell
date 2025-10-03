NAME	=	wildcard

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3 #-fsanitize=address
LDFLAGS	=	-lreadline -lncurses

SRCS	=	 ../tokenizer/bool_funcs.c ./wildcard_expander.c\

VALGRIND =	valgrind --leak-check=full --show-leak-kinds=all

VALCHILDEN =	valgrind  --suppressions=readline.supp --track-fds=yes --trace-children=yes

OBJS	=	$(SRCS:%.c=%.o)

LIBFT_DIR	=	../libft
LIBFT_A		=	$(LIBFT_DIR)/libft.a

# PARS_ENV = ../parsing_env

all: $(LIBFT_A)  $(NAME)

# $(PARS_ENV):
# 	$(MAKE) -C $(PARS_ENV)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

val: $(NAME) clean
	$(VALGRIND) ./$(NAME)

child: $(NAME) clean
	$(VALCHILDEN) ./$(NAME)

re: fclean all

.PHONY: all clean fclean re
