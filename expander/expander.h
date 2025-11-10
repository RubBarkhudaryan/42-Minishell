/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:04:28 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/25 21:04:28 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H

# define EXPANDER_H

# include "../env/env_parser.h"
# include "../tokenizer/tokenizer.h"
# include <dirent.h>
# include <stdbool.h>

typedef struct s_shell		t_shell;
typedef struct s_token		t_token;
typedef struct s_redir_cmd	t_redir_cmd;

typedef struct s_expand
{
	char	*piece;
	char	*res;
	char	*tk;
}	t_expand;

/*token expansion*/
char	*expand_nested_quote(char *token, int is_here_doc);
char	*expand_dollar_token(char *token, t_shell *shell, bool skip_expand);
char	*expand_wildcard(char *wildcard);

/*expansion helpers*/
int		is_var_name_char(char c);
// int		check_expand_case(char *token);
char	*join_args(char *str1, char *str2);
void	change_val(char **str1, char **str2);
void	add_val(t_expand *exp, int *i);
void	refresh_args_val(t_expand *exp, char *join, int *ind, int inc_by);

#endif
