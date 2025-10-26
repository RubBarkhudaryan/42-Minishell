/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:09:32 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/26 22:57:08 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

int	run_here_doc(t_cmd *cmd, char *delimiter, char *filename, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (free(filename), perror("minishell"), EXIT_FAILURE);
	if (pid == 0)
		run_heredoc_child(cmd, delimiter, filename, shell);
	return (waitpid(pid, &status, 0), get_exit_code(status));
}

char	*open_check_filename(void)
{
	char	*filename;
	char	*tmp;
	int		index;

	index = 0;
	while (1)
	{
		tmp = ft_itoa(index++);
		if (!tmp)
		{
			perror("minishell");
			return (NULL);
		}
		filename = ft_strjoin("/tmp/.her_doc", tmp);
		if (!filename)
		{
			free(tmp);
			perror("minishell");
			return (NULL);
		}
		free(tmp);
		if (access(filename, F_OK) != 0)
			return (filename);
		free(filename);
	}
}

int	cheak_expand_heredoc(char **deleimiter)
{
	int		i;
	char	*tmp;
	char	*new_delim;

	i = 0;
	while ((*deleimiter)[i])
	{
		if ((*deleimiter)[i] == '\'' || (*deleimiter)[i] == '\"')
		{
			tmp = ft_strtrim(*deleimiter, "\'\"");
			if (!tmp)
			{
				perror("minishell");
				return (0);
			}
			new_delim = tmp;
			free(*deleimiter);
			*deleimiter = new_delim;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*here_doc(t_cmd *cmd, char *delimiter, t_shell *shell)
{
	char	*file_name;

	file_name = open_check_filename();
	if (!file_name)
		return (NULL);
	cmd->redirs_cmd->redirs->is_expanded = cheak_exp_heredoc(&delimiter);
	// printf("heredoc delimiter: [%s]\n", delimiter);
	// printf("heredoc : [%d]\n", cmd->redirs_cmd->redirs->is_expanded);
	shell->last_exit_code = run_here_doc(cmd, delimiter, file_name, shell);
	if (shell->last_exit_code == EXIT_FAILURE)
		return (free(file_name), NULL);
	return (file_name);
}
