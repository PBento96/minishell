/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/05/29 21:30:07 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create_child_process(t_data *data, int pipefd[2],
	int cmd_index, char **cmd_args)
{
	if (cmd_index < data->cmd_count)
		ft_setup_pipes(pipefd);
	data->pids[cmd_index] = fork();
	if (data->pids[cmd_index] == -1)
		ft_pipe_error(data, cmd_args);
	else if (data->pids[cmd_index] == 0)
	{
		ft_handle_pipes(data, pipefd, data->commands[cmd_index], cmd_index);
		ft_execute_command(data, cmd_args,
			data->commands[cmd_index].tokens->type);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Safely closes a file descriptor if it's valid                           */
/*   Updates the descriptor to -1 after closing to prevent double closing    */
/*   Ignores descriptors that are already set to -1                          */
/* ************************************************************************** */
void	ft_safe_close(int *fd)
{
	if (fd && *fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

static void	ft_handle_parent(t_data *data, int pipefd[2], int cmd_index)
{
	if (cmd_index < data->cmd_count)
		close(pipefd[1]);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	if (cmd_index < data->cmd_count)
		data->prev_pipe = pipefd[0];
}

/* ************************************************************************** */
/*                                                                            */
/*   Handles execution of commands in a pipeline                             */
/*   Waits for certain processes when needed                                 */
/*   Creates child processes for command execution                           */
/*   Manages parent process handling of pipes                                */
/* ************************************************************************** */
void	ft_handle_command(t_data *data, int *pipefd, int cmd_index,
	char **cmd_args)
{
	if (cmd_index > 0 && data->commands[cmd_index - 1].redir.out_fd
		!= STDOUT_FILENO && data->commands[cmd_index].redir.in_fd
		!= STDIN_FILENO)
	{
		if (data->pids[cmd_index - 1] > 0)
			waitpid(data->pids[cmd_index - 1], NULL, 0);
	}
	ft_create_child_process(data, pipefd, cmd_index, cmd_args);
	if (data->pids[cmd_index] > 0)
		ft_handle_parent(data, pipefd, cmd_index);
}

/* ************************************************************************** */
/*                                                                            */
/*   Executes a lone builtin command without forking                         */
/*   Sets up file redirection for stdin and stdout                           */
/*   Preserves original file descriptors                                     */
/*   Restores original stdin and stdout after execution                      */
/* ************************************************************************** */
void	ft_execute_lone_builtin(t_data *data, int cmd_index, char **cmd_args)
{
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (data->commands[cmd_index].redir.in_fd != STDIN_FILENO)
	{
		dup2(data->commands[cmd_index].redir.in_fd, STDIN_FILENO);
		close(data->commands[cmd_index].redir.in_fd);
	}
	if (data->commands[cmd_index].redir.out_fd != STDOUT_FILENO)
	{
		dup2(data->commands[cmd_index].redir.out_fd, STDOUT_FILENO);
		close(data->commands[cmd_index].redir.out_fd);
	}
	data->pids[cmd_index] = -1;
	write(1, "Executing Lone Builtin\n", 23);
	ft_execute_builtin(data, cmd_args);
	data->status = 0;
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
