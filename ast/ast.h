/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:42:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/17 02:00:58 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
#define AST_H

#include "../redirection/here_doc/here_doc.h"
#include "../syntax/syntax.h"
#include "../tokenizer/tokenizer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_MSG "minishell: syntax error near unexpected token `"

typedef struct s_shell t_shell;
typedef struct s_token t_token;
typedef struct s_redir t_redir;
typedef enum e_token_type t_token_type;

typedef enum e_ast_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
} t_ast_node_type;

typedef struct s_cmd
{
	char *cmd_name;
	char **args;
	t_token *token_list;
	t_redir *redirs_cmd;
	int in_pipeline;
	int out_pipeline;
} t_cmd;

/*AST Struct*/
typedef struct s_ast
{
	t_cmd *cmd;
	t_ast_node_type type;
	struct s_ast *left;
	struct s_ast *right;
} t_ast;

/*AST builder*/
void free_ast(t_ast *node, int flag_unlink_heredoc);
t_ast	*build_ast(t_token **token_list, t_shell *shell);
t_cmd	*make_cmd(t_token **list, t_shell *shell);
t_token *find_matching_parenthesis(t_token *start, int *ret_count);
int count_args(t_token *current);
int fill_args(t_cmd *cmd, t_token **token_list, int arg_count);
t_cmd *parse_redirs_ast(t_cmd *cmd, t_token **token_list, t_shell *shell);
int is_valid_token_type(t_token_type type);
t_ast *parse_regular_command(t_token **token_list, t_shell *shell);
t_ast *parse_subshell(t_token **token_list, t_shell *shell);
t_ast *create_ast_node(t_ast *left, t_ast *right, int type, t_cmd *cmd);
void throw_error(char *target);

/*AST builder utils*/
void print_ast(t_ast *node, int level);
void free_cmd(t_cmd *cmd, int flag_unlink_heredoc);
int is_subshell_paren(t_token *token);
int is_redirection_type(t_token *token);
char **ft_splitdup(char **args);
t_cmd	*init_cmd();
t_ast *parse_ast(t_token **token_list, t_shell *shell);
#endif

/*
grelu em mi hat funkcia vor ete ast->node null a ed token listi elem-ic unenq error
*/