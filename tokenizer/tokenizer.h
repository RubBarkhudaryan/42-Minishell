/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:54:07 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/01 13:15:10 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H

# define TOKENIZER_H

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
}	t_token;

/*token type enum*/
typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_OR,
	TK_AND,
	TK_DOLLAR,
	TK_APPEND,
	TK_HEREDOC,
	TK_REDIR_INPUT,
	TK_REDIR_OUTPUT,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE,
	TK_L_PARENTHESIS,
	TK_R_PARENTHESIS,
	TK_ERROR
}	t_token_type;

/*tokenizer*/
t_token	*tokenize(char *input);

/*tokenization process*/
int		make_quoted_token(t_token **head, char *str, int i);
int		make_word_token(t_token **head, char *str, int i);
int		make_specials_token(t_token **head, char *str, int i);

/*tokenizer utils*/
void	add_token(t_token **last_elem, char *value);
void	free_token_list(t_token *head);
int		get_parenthesis_token_type(char *value);
int		get_token_type(char *value);
int		get_quoted_token_type(char *value);

/*tk functions*/
int		tk_strcmp(char *str1, char *str2);
int		tk_isalpha(char c);
int		tk_isspace(char c);
int		tk_strlen(char *str);
int		tk_inset(char c, char *set);
char	*tk_substr(char *str, unsigned int start, size_t len);
char	*tk_strdup(char *str);

#endif