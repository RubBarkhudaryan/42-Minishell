NAME	=	token

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3
LDFLAGS	=	-lreadline -lncurses

SRCS	=	main.c tokenizer_utils.c tokenizer.c token_maker.c bool_funcs.c int_funcs.c str_funcs.c\
			../syntax_analysis/syntax_utils.c ../syntax_analysis/syntax.c

OBJS	=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re