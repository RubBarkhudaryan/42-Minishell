/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:31 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/03 16:09:09 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_PARSER_H
# define ENV_PARSER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

// flag -> 0 - not exported, 1 - exported
typedef struct s_env
{
	char			*key;
	char			*value;
	int				flag;
	struct s_env	*next;
}					t_env;

t_env				*parse_environment(char **envp);
t_env				*search_node(char *key, t_env *env);
t_env				*env_new_node(char *key, char *value);
int					add_env_end(t_env **env, char *key, char *value);
char				**convert_envp_to_string(t_env *head);
char				*get_value_from_env(t_env *head, char *key);
void				remove_env_node(t_env **head, char *key);
int					replace_env_value(char *key, char *value, t_env *head);

int					args_len(char **args);
void				free_split(char **ret);
void				free_env_list(t_env *head);
int					env_list_size(t_env *head);
#endif
