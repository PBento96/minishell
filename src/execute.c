/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/22 20:39:23 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*   Executes a command with the given arguments                             */
/*   For builtins, runs them directly                                        */
/*   For external commands, uses execve with proper path                     */
/*   Handles cleanup and exits the child process when done                   */
/* ************************************************************************** */
void	ft_execute_command(t_data *data, char **cmd_args, t_token_type type)
{
	int	i;

	i = 0;
	if (type == BUILTIN)
		ft_execute_builtin(data, cmd_args);
	else
	{
		if (data->cmd_path == NULL)
		{
			ft_printf(C_RED"%s: Command not found\n"RESET_ALL, cmd_args[0]);
			ft_free_array((void **)cmd_args);
			exit(EXIT_FAILURE);
		}
		if (execve(data->cmd_path, cmd_args, data->env))
		{
			perror("execve");
			ft_free((void **)&data->cmd_path);
			ft_free_array((void **)cmd_args);
			exit(EXIT_FAILURE);
		}
	}
	ft_free((void **)&data->cmd_path);
	ft_free_array((void **)cmd_args);
	exit(EXIT_FAILURE);
}

static void	ft_prepare_command(t_data *data, int cmd_index, char ***cmd_args)
{
	*cmd_args = ft_tokens_to_args(&data->commands[cmd_index]);
	ft_getpath(data, *cmd_args[0]);
}

static void ft_create_child_process(t_data *data, int pipefd[2],
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
/*   Executes commands in the pipeline                                       */
/*   Sets up pipes and heredoc synchronization                               */
/*   Handles execution flow for builtins and external commands               */
/*   Manages command redirection and cleanup                                 */
/* ************************************************************************** */
static void	ft_setup_heredoc_sync(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		pipe(data->heredoc_sync[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Executes a lone builtin command without forking                         */
/*   Sets up file redirection for stdin and stdout                           */
/*   Preserves original file descriptors                                     */
/*   Restores original stdin and stdout after execution                      */
/* ************************************************************************** */
static void	ft_execute_lone_builtin(t_data *data, int cmd_index, char **cmd_args)
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
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

/* ************************************************************************** */
/*                                                                            */
/*   Handles execution of commands in a pipeline                             */
/*   Waits for certain processes when needed                                 */
/*   Creates child processes for command execution                           */
/*   Manages parent process handling of pipes                                */
/* ************************************************************************** */
static void	ft_handle_command(t_data *data, int *pipefd, int cmd_index,
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
/*   Performs cleanup operations after command execution                     */
/*   Closes heredoc synchronization pipes                                    */
/*   Waits for child processes to complete                                   */
/*   Closes any redirected file descriptors                                  */
/* ************************************************************************** */
static void	ft_cleanup_execution(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		close(data->heredoc_sync[i][0]);
		close(data->heredoc_sync[i][1]);
		i++;
	}
	ft_wait_children(data, data->pids);
	i = 0;
	while (i <= data->cmd_count)
	{
		ft_close_redirect_fds(&data->commands[i].redir);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Main command execution controller                                       */
/*   Allocates memory for process IDs                                        */
/*   Processes commands one by one                                           */
/*   Handles special case for lone builtins                                  */
/*   Coordinates cleanup after execution                                     */
/* ************************************************************************** */
void	ft_execute(t_data *data)
{
	int		pipefd[2];
	int		cmd_index;
	char	**cmd_args;

	ft_setup_heredoc_sync(data);
	cmd_index = -1;
	data->pids = malloc((data->cmd_count + 1) * sizeof(pid_t));
	if (!data->pids)
		return ;
	data->prev_pipe = -1;
	while (++cmd_index < data->cmd_count + 1 && !g_signal)
	{
		ft_prepare_command(data, cmd_index, &cmd_args);
		if (data->cmd_count == 0 &&
			data->commands[cmd_index].tokens->type == BUILTIN)
			ft_execute_lone_builtin(data, cmd_index, cmd_args);
		else
			ft_handle_command(data, pipefd, cmd_index, cmd_args);
		ft_free_cmd(data, cmd_args);
	}
	ft_cleanup_execution(data);
}
