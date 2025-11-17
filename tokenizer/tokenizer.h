/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:54:07 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/17 02:15:00 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define REDIR_ERR "minishell: syntax error near unexpected token `newline'\n"

# include "../ast/ast.h"
# include "../execute/execute.h"
# include "../expander/expander.h"
# include "../libft/libft.h"
# include "../env/env_parser.h"
# include "../signals/signals.h"
# include "../syntax/syntax.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmd	t_cmd;

/*token list*/
typedef struct s_token
{
	char				*token;
	int					type;
	bool				is_subshell;
	struct s_token		*next;
}						t_token;

/*token type enum*/
typedef enum e_token_type
{
	TK_WORD,
	TK_REDIR_INPUT,
	TK_REDIR_OUTPUT,
	TK_APPEND,
	TK_HEREDOC,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_L_PARENTHESIS,
	TK_R_PARENTHESIS,
	TK_ERROR
}						t_token_type;

/*redir struct*/
typedef struct s_redir
{
	t_token_type		type;
	int					is_expanded;
	char				*filename;
	int					heredoc_fd;
	struct s_redir		*next;
}						t_redir;

/*tokenizer*/
t_token	*tokenize(char *input);

/*tokenization process*/
int		make_word_token(t_token **head, char *str, int i);
int		make_specials_token(t_token **head, char *str, int i);

/*tokenizer utils*/
int		ft_inset(char c, char *set);
int		ft_isspace(char c);
void	add_token(t_token **last_elem, char *value);
void	free_token_list(t_token *head);
void	print_token_list(t_token *head);
int		get_parenthesis_token_type(char *value);
int		get_token_type(char *value);
int		ft_is_word_part(char c);

/*redirs list builders*/
t_redir			*init_redir(int type, char *filename);
void			add_redir(t_redir *redirs, t_redir *new_node);
void			free_redir_list(t_redir *redir, int flag_unlink_heredoc);

#endif
