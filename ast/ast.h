/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:42:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/02 15:45:12 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../syntax_analysis/syntax.h"

/*AST Struct*/
typedef struct s_ast
{
	char			*val;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*AST builder*/
t_ast	*build_ast(t_token *token_list);

/*AST builder utils*/
