/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:07:01 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/01 13:16:16 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H

# define SYNTAX_H

# include "../tokenizer/tokenizer.h"

/*analyze tokens before making AST*/

int	analyze(t_token *token_list);

/*utils for analyzer*/
int	check_syntax_errors(t_token *token);
int	is_operator(t_token *token);
int	is_redir(t_token *token);

#endif