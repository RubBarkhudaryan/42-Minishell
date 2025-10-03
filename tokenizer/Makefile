NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3 #-fsanitize=address
LDFLAGS	=	-lreadline -lncurses

SRCS	=	main.c tokenizer_utils.c tokenizer.c token_maker.c bool_funcs.c parse_subshell.c \
			../expander/expander.c ../expander/expand_helpers.c  \
			./redirection/redirs.c ./redirection/redir_helpers.c \
			 ./redirection/here_doc/here_doc_shell.c ./redirection/here_doc/here_doc_helper.c\
			../syntax_analysis/syntax_utils.c ../syntax_analysis/syntax.c \
			../ast/ast.c ../ast/ast_helper.c\
			../parsing_env/env_parser.c ../parsing_env/env_utils.c  ../parsing_env/parsing_helper.c \
			 ./execute/execute.c ./execute/cmd_exec.c ./execute/builtin_exec.c ./execute/utils.c  ./execute/exec_utils.c ./execute/pipe_exec.c\
			../built_in/cd.c ../built_in/echo.c ../built_in/env.c ../built_in/export.c\
			 ../built_in/export_utils.c ../built_in/exit.c\
			../built_in/pwd.c ../built_in/unset.c ../built_in/utils.c\

VALGRIND =	valgrind --leak-check=full --show-leak-kinds=all  --suppressions=readline.supp

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
