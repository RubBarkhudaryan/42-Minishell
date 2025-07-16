NAME	=	token

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3

SRCS	=	main.c tokenizer_utils.c tokenizer.c

OBJS	=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re