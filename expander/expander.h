/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:29:57 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/11 18:29:57 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H

# define EXPANDER_H
# include "../tokenizer/tokenizer.h"
# include "../parsing_env/env_parser.h"
# include <dirent.h>

typedef struct s_expand
{
	char	*piece;
	char	*res;
	char	*tk;
	int		is_here_doc;
}	t_expand;

/*token expansion*/
void				expand_tokens(t_token **token_list, t_env *env);
char				*expand_dollar_token(char *token, t_env *env);
char				*expand_nested_quote(char *token, t_env *env,
						int is_here_doc);

/*expansion helpers*/
int					is_var_name_char(char c);
char				*join_args(char *str1, char *str2);
void				change_val(char **str1, char **str2);
int					check_nested_quote(char curr_tk, char next_tk);
void				handle_dollar(t_expand *exp, int *i, t_env *env);
void				add_val(t_expand *exp, t_env *env, int *i, char quote);
void				refresh_args_val(t_expand *exp, char *join,
						int *ind, int inc_by);

/*wildcard handle*/
char				*expand_wildcard(char *wildcard);

#endif