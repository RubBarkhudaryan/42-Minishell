/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:42:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:51 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_token	t_token;

# include "../syntax_analysis/syntax.h"
# include "../tokenizer/tokenizer.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_ast_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}						t_ast_node_type;

/*AST Struct*/
typedef struct s_ast
{
	t_token				*cmd;
	t_ast_node_type		type;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

/*AST builder*/
void					free_ast(t_ast *node);
t_ast					*build_ast(t_token **token_list);
void					print_ast(t_ast *node, int level);

/*AST builder utils*/
#endif
