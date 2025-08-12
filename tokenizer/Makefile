NAME	=	token

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3
LDFLAGS	=	-lreadline -lncurses

SRCS	=	main.c tokenizer_utils.c tokenizer.c token_maker.c bool_funcs.c int_funcs.c str_funcs.c\
			../syntax_analysis/syntax_utils.c ../syntax_analysis/syntax.c ../ast/ast.c ./execute/execute.c \

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


re: fclean all

.PHONY: all clean fclean re

