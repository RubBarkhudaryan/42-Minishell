/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:07:01 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/24 01:48:50 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H

# define SYNTAX_H

# include "../ast/ast.h"
# include "../tokenizer/tokenizer.h"

typedef struct s_shell		t_shell;
typedef struct s_token		t_token;
typedef struct s_redir_cmd	t_redir_cmd;
typedef struct s_ast		t_ast;

/*analyze tokens before making AST*/

int							syntax_analyze(t_ast *ast);

/*utils for analyzer*/
int							is_redir(t_token *token);

#endif
