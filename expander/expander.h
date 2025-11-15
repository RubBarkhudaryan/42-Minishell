/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:15:11 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/14 22:15:11 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H

# define EXPANDER_H

# include "../ast/ast.h"
# include "../env/env_parser.h"
# include "../tokenizer/tokenizer.h"
# include <dirent.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_ast		t_ast;
typedef struct s_cmd		t_cmd;
typedef struct s_shell		t_shell;
typedef struct s_token		t_token;
typedef struct s_redir_cmd	t_redir_cmd;

typedef struct s_expand
{
	char	*piece;
	char	*res;
	char	*tk;
}	t_expand;

typedef struct s_file
{
	char			*filename;
	struct s_file	*next;
}	t_file;

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
}	t_index;

/*token expansion*/
void	expand_command_variables(t_ast *ast, t_shell *shell);
char	*expand_nested_quote(char *token);
char	*expand_dollar_token(char *token, t_shell *shell, bool expand);
char	**expand_wildcard(char *source);

/*expansion helpers*/
int		is_var_name_char(char c);
char	*join_args(char *str1, char *str2);
void	change_val(char **target, char **source);
void	refresh_val(char **target, char *source);
void	add_val(t_expand *exp, int *i);
void	refresh_args_val(t_expand *exp, char *join, int *ind, int inc_by);
int		count_segments(const char *token);
char	**split_by_quotes(const char *token);

/*wildcard maker*/
char	*make_wildcard(char *source);
int		wildcard_match(const char *pattern, const char *str);

/*wildcard utils*/
void	free_wildcard_tools(t_file *files, DIR *dir, t_expand *exp);
char	*get_filename(char *wildcard);
char	*get_extension(char *wildcard);
char	*join_filenames(char *str1, char *str2, char delim);

/*wildcard matching funcs*/
int		wildcard_match(const char *pattern, const char *str);
int		is_matching_with_wildcard(char *pattern, char *file, int show_hidden);

/**/
int		set_show_hiddens(char *pattern);
void	append_match(t_expand *file, char *filename);
void	process_files(t_expand *file, t_file *files, int show_hiddens);

/*wildcard maker utils*/
int		check_asterisk(t_cmd *cmd);
char	**join_expand_wildcards(t_cmd *cmd, int *len);
char	**join_split(char **join, char **tmp);
int		check_str(char *tmp);
void	update_args(t_cmd *cmd, int len, char **expand_asterisks);
void	append_char(t_expand *w, char c);
void	append_star(t_expand *w);
int		match_question_or_char(const char **p, const char **s);
int		match_star(const char **p, const char **s,
			const char **star, const char **ss);
int		backtrack_star(const char **p, const char **s,
			const char **star, const char **ss);

#endif
