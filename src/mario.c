/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:30:00 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/06 11:57:49 by joseferr         ###   ########.fr       */
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
}

void ft_handle_pipes(t_data *data, int pipefd[2], int command)
{
	// If this command has input from a previous pipe
	if (data->prev_pipe != -1)
	{
		// Only redirect if no file redirection has been set up
		if (data->commands[command].redir.in_fd == 0)
			dup2(data->prev_pipe, STDIN_FILENO);
		else {
			// We have a file redirection, apply it
			dup2(data->commands[command].redir.in_fd, STDIN_FILENO);
			// Close it after duplicating
			close(data->commands[command].redir.in_fd);
		}

		close(data->prev_pipe);
	}
	else if (data->commands[command].redir.in_fd > 0)
	{
		// No pipe but we have a file redirection
		dup2(data->commands[command].redir.in_fd, STDIN_FILENO);
		// Close it after duplicating
		close(data->commands[command].redir.in_fd);
	}

	if (command < data->cmd_count)
	{
		// Only redirect output to pipe if no file redirection exists
		if (data->commands[command].redir.out_fd == 1)
			dup2(pipefd[1], STDOUT_FILENO);
		else {
			// We have a file redirection, apply it
			dup2(data->commands[command].redir.out_fd, STDOUT_FILENO);
			// Close it after duplicating
			close(data->commands[command].redir.out_fd);
			data->commands[command].redir.out_fd = 1;
		}

		close(pipefd[1]);
		data->prev_pipe = pipefd[0];
	}
	else
	{
		close(pipefd[0]);
		// Apply any output redirection for the last command
		if (data->commands[command].redir.out_fd > 1) {
			dup2(data->commands[command].redir.out_fd, STDOUT_FILENO);
			// Close it after duplicating
			close(data->commands[command].redir.out_fd);
			data->commands[command].redir.out_fd = 1;
		}
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
