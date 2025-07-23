/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:31 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/22 20:53:30 by apatvaka         ###   ########.fr       */
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
	int flag; // 0 - not exported, 1 - exported
	struct s_env	*next;
}					t_env;

t_env				*parse_environment(char **envp);
char	*get_value_from_env(t_env *head, char *key); // this is new
int					replace_env_value(char *key, char *value, t_env *head,
						int flag);
char				**convert_envp_to_string(t_env *head);
t_env				*new_node(char *key, char *value);

void				free_split(char **ret);
void				free_env_list(t_env *head);
int					env_list_size(t_env *head);
int	args_len(char **args); // The function gives the length of the arguments.
#endif
