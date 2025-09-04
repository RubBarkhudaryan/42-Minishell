/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:42:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/02 16:27:45 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

// Добавьте в самое начало файла
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

typedef struct s_cmd
{
	char				*cmd_name;
	char				**args;
	int					in_pipeline;
	int					out_pipeline;

}						t_cmd;

/*AST Struct*/
typedef struct s_ast
{
	t_cmd				*cmd;
	t_ast_node_type		type;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

/*AST builder*/
void					free_ast(t_ast *node);
t_ast					*build_ast(t_token **token_list);
t_cmd					*give_token_for_cmd(t_token **token_list);
void					print_ast(t_ast *node, int level);
void					free_cmd(t_cmd *cmd);
/*AST builder utils*/
#endif
