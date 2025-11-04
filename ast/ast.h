/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:42:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/03 19:44:09 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../syntax_analysis/syntax.h"
# include "../tokenizer/redirection/here_doc/here_doc.h"
# include "../tokenizer/tokenizer.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_shell		t_shell;
typedef struct s_token		t_token;
typedef struct s_redir_cmd	t_redir_cmd;
typedef enum e_token_type	t_token_type;

typedef enum e_ast_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}							t_ast_node_type;

typedef struct s_cmd
{
	char					*cmd_name;
	char					**args;
	t_token					*token_list;
	t_redir_cmd				*redirs_cmd;
	int						in_pipeline;
	int						out_pipeline;
}							t_cmd;

/*AST Struct*/
typedef struct s_ast
{
	t_cmd					*cmd;
	t_ast_node_type			type;
	struct s_ast			*left;
	struct s_ast			*right;
}							t_ast;

/*AST builder*/

void						free_ast(t_ast *node, int flag_unlink_heredoc);
t_ast						*build_ast(t_token **token_list, t_shell *shell);
t_cmd						*give_token_for_cmd(t_token **token_list,
								t_shell *shell);
t_token						*find_matching_parenthesis(t_token *start,
								int *ret_count);
void						set_type(t_ast *node, int type);
void						set_cmd(t_ast *node);
int							count_args(t_token *current);
int							fill_args(t_cmd *cmd, t_token **token_list,
								int arg_count);
// void						set_cmd(t_ast *node);
void						set_type(t_ast *node, int type);
t_cmd						*parse_redirs_ast(t_cmd *cmd, t_token **token_list,
								t_shell *shell);
int							is_valid_token_type(t_token_type type);
t_ast						*handle_regular_command(t_token **token_list,
								t_shell *shell);
t_ast						*handle_subshell(t_token **token_list,
								t_shell *shell);
/*AST builder utils*/
void						print_ast(t_ast *node, int level);
void						free_cmd(t_cmd *cmd, int flag_unlink_heredoc);

#endif
