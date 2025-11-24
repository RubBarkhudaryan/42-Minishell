NAME	=	minishell

CC		=	cc
CFLGS	=	-Wall -Wextra -Werror -g3
LDFLAGS	=	-lreadline -lncurses


SRCS	=	main.c main_utils.c\
			./tokenizer/tokenizer_utils.c ./tokenizer/tokenizer.c ./tokenizer/token_maker.c ./tokenizer/token_checker.c \
			./expander/expander.c ./expander/expand_helpers.c ./expander/expand_utils.c ./expander/expand_commands.c\
			./expander/wildcard_expander.c ./expander/wildcard_helpers.c ./expander/wildcard_maker_utils.c ./expander/wildcard_checker_utils.c ./expander/wildcard_match_utils.c\
			./signals/signals.c ./signals/signals2.c \
			./redirection/redirs.c redirection/redir_free.c ./redirection/redir_apply.c ./redirection/redir_helpers.c \
			./redirection/here_doc/here_doc_shell.c ./redirection/here_doc/here_doc_helper.c\
			./ast/ast.c ./ast/ast_helper.c ./ast/ast_redir.c ./ast/ast_tools.c ./ast/ast_cmd.c ./ast/ast_utils.c\
			./env/env_parser.c ./env/env_utils.c ./env/parsing_helper.c \
			./execute/execute.c ./execute/cmd_exec.c ./execute/builtin_exec.c ./execute/utils.c ./execute/exec_utils.c ./execute/pipe_exec.c ./execute/env_var_update.c \
			./built_in/cd.c ./built_in/echo.c ./built_in/env.c ./built_in/export.c\
			./built_in/export_utils.c ./built_in/exit.c\
			./built_in/pwd.c ./built_in/unset.c ./built_in/utils.c ./built_in/exit_utils.c

VALGRIND =	valgrind --leak-check=full --show-leak-kinds=all  --suppressions=readline.supp

VALCHILDEN =	valgrind  --suppressions=readline.supp --track-fds=yes --trace-children=yes


OBJS	=	$(SRCS:%.c=%.o)

LIBFT_DIR	=	./libft
LIBFT_A		=	$(LIBFT_DIR)/libft.a

all: $(LIBFT_A)  $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLGS) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

val: $(NAME) clean
	$(VALGRIND) ./$(NAME)
#
#child: $(NAME) clean
#	$(VALCHILDEN) ./$(NAME)
#run: $(NAME) clean
#	./$(NAME)
#co: $(NAME) clean
#	./$(NAME)

re: fclean all

.PHONY: all clean fclean re
