NAME		= minishell

CC	= cc
RM	= rm -f

SRC	= src/main.c utils/utils.c built_in/echo.c
OBJ_DIR	= obj
OBJ	= $(SRC:%.c=$(OBJ_DIR)/%.o)

INC_DIR		= includes
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

CFLAGS		= -Wall -Wextra -Werror -g3 -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -lft -lreadline -lncurses

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
