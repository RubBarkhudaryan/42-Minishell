/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:09:32 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/08 14:13:21 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

int	run_here_doc(t_cmd *cmd, t_here_doc here_doc_data, t_shell *shell)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (free(here_doc_data.filename), perror("minishell"),
			EXIT_FAILURE);
	if (pid == 0)
	{
		handle_child_signals();
		run_heredoc_child(cmd, here_doc_data, shell);
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler_parent);
	if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		shell->last_exit_code = get_exit_code(status);
	}
	else
		shell->last_exit_code = WEXITSTATUS(status);
	return (shell->last_exit_code);
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

	i = 0;
	while ((*deleimiter)[i])
	{
		if ((*deleimiter)[i] == '\'' || (*deleimiter)[i] == '\"')
		{
			tmp = expand_nested_quote(*deleimiter, 0);
			if (!tmp)
			{
				perror("minishell");
				return (0);
			}
			free(*deleimiter);
			*deleimiter = tmp;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*here_doc(t_cmd *cmd, char *delimiter, t_shell *shell)
{
	char		*file_name;
	t_here_doc	here_doc_data;

	file_name = open_check_filename();
	if (!file_name)
		return (NULL);
	cmd->redirs_cmd->redirs->is_expanded = cheak_expand_heredoc(&delimiter);
	here_doc_data.delimiter = delimiter;
	here_doc_data.filename = file_name;
	shell->last_exit_code = run_here_doc(cmd, here_doc_data, shell);
	if (shell->last_exit_code != 0)
	{
		free(file_name);
		free(delimiter);
		return (NULL);
	}
	free(delimiter);
	return (file_name);
}
