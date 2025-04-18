/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:30:00 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/18 16:59:57 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_wait_children(t_data *data, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	if (pids)
	{
		while (i <= data->cmd_count)
		{
			if (pids[i] > 0)
				waitpid(pids[i], &status, 0);
			i++;
		}
		free(pids);
	}
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
}

void	ft_handle_pipes(t_data *data, int pipefd[2], t_command command, int cmd_index)
{
	int heredoc_pipe[2];

	// Handle input redirection
	if (command.redir.delim)
	{
		ft_get_delim_buf(&command, command.redir.delim);
		if (command.redir.delim_buf)
		{
			// Create a pipe to redirect the delim_buf content to stdin
			if (pipe(heredoc_pipe) == -1)
			{
				perror("pipe");
				return;
			}
			// Write the collected content to the pipe
			write(heredoc_pipe[1], command.redir.delim_buf,
				ft_strlen(command.redir.delim_buf));
			close(heredoc_pipe[1]);

			// Redirect the pipe's read end to stdin
			dup2(heredoc_pipe[0], STDIN_FILENO);
			close(heredoc_pipe[0]);
		}
	}
	else if (command.redir.in_fd != STDIN_FILENO)
	{
		dup2(command.redir.in_fd, STDIN_FILENO);
		close(command.redir.in_fd);
	}
	else if (cmd_index > 0) // Use previous pipe if no input redirection
	{
		dup2(data->prev_pipe, STDIN_FILENO);
		close(data->prev_pipe);
	}

	// Handle output redirection
	if (command.redir.out_fd != STDOUT_FILENO)
	{
		dup2(command.redir.out_fd, STDOUT_FILENO);
		close(command.redir.out_fd);
	}
	else if (cmd_index < data->cmd_count) // Use pipe if no output redirection
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

void	ft_setup_pipes(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	ft_pipe_error(t_data *data, char **cmd_args)
{
	perror("fork");
	ft_free_cmd(data, cmd_args);
	return ;
}
