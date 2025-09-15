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

typedef struct s_expand
{
	char	*piece;
	char	*res;
	char	*tk;
	int		is_here_doc;
}	t_expand;

/*token expansion*/
void				change_val(char **str1, char **str2);
void				expand_tokens(t_token **token_list, t_env *env);
char				*join_args(char *str1, char *str2);
char				*expand_dollar_token(char *token, t_env *env);
char				*expand_nested_quote(char *token, t_env *env, int is_here_doc);

#endif