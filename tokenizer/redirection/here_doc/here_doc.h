/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:26:51 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/02 20:30:45 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "../../../ast/ast.h"
# include "../../../expander/expander.h"
# include "../../../libft/libft.h"
# include "../../../parsing_env/env_parser.h"
# include "../../../syntax_analysis/syntax.h"
# include "../../execute/execute.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;

char					*here_doc(t_cmd *cmd, char *delimiter, t_shell *shell);
void					run_heredoc_child(t_cmd *cmd, char *delimiter,
							char *filename, t_shell *shell);
char					*open_check_filename(void);
void					here_doc_clean(char **shell);
int						ft_isspace(char c);
int						ft_inset(char c, char *set);

#endif
