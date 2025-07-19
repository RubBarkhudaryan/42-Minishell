/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:31 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/19 16:52:05 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_PARSER_H
# define ENV_PARSER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env				*parse_environment(char **envp);
char				**convert_envp_to_string(t_env *head);
void				free_split(char **ret);
t_env				*new_node(char *key, char *value);
void				free_env_list(t_env *head);
int					env_list_size(t_env *head);
#endif
