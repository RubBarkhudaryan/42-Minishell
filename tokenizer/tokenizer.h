/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:54:07 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/26 17:25:49 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H

# define TOKENIZER_H

#include "./execute/execute.h"
# include "../ast/ast.h"
# include "../libft/libft.h"
# include "../parsing_env/env_parser.h"
# include "../syntax_analysis/syntax.h"
# include "./execute/execute.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*token list*/
typedef struct s_token
{
	char			*token;
	int				token_type;
	struct s_token	*next;
}					t_token;

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
	TK_DOLLAR,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE,
	TK_ERROR
}					t_token_type;

/*tokenizer*/
t_token				*tokenize(char *input);

/*tokenization process*/
int					make_quoted_token(t_token **head, char *str, int i);
int					make_word_token(t_token **head, char *str, int i);
int					make_specials_token(t_token **head, char *str, int i);

/*tokenizer utils*/
int					ft_inset(char c, char *set);
int					ft_isspace(char c);
void				add_token(t_token **last_elem, char *value);
void				free_token_list(t_token *head);
void				print_token_list(t_token *head);
int					get_parenthesis_token_type(char *value);
int					get_token_type(char *value);
int					get_quoted_token_type(char *value);
int					parse_subshell(t_token **head, char *str, int i);

/*token expansion*/
void				expand_tokens(t_token **token_list, t_env *env);

/*tk functions*/
int					ft_isspace(char c);
int					ft_inset(char c, char *set);

#endif
