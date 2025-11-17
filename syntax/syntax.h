/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:07:01 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/17 02:15:00 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H

# define SYNTAX_H

# include "../ast/ast.h"
# include "../tokenizer/tokenizer.h"
# include <stdbool.h>

typedef struct s_shell		t_shell;
typedef struct s_token		t_token;
typedef struct s_ast		t_ast;

/*analyze tokens before making AST*/

int		syntax_analyze(t_ast *ast);

/*utils for analyzer*/
int		validate_parenthesis(t_token *token_list);
int		is_redir(t_token *token);
int		check_quoted_str(t_token *head);
bool	check_syntax(t_token *token_list, char *line, t_shell *shell);

#endif
