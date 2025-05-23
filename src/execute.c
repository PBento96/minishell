/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/05/23 20:27:11 by joseferr         ###   ########.fr       */
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
void ft_execute_command(t_data *data, char **cmd_args, t_token_type type)
{
	int exit_status = EXIT_SUCCESS;

	if (type == BUILTIN)
	{
		ft_execute_builtin(data, cmd_args);
		exit_status = data->status;
	}
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
			exit_status = EXIT_FAILURE;
		}
	}
	ft_free((void **)&data->cmd_path);
	ft_free_array((void **)cmd_args);
	exit(exit_status);
}

static void	ft_prepare_command(t_data *data, int cmd_index, char ***cmd_args)
{
	*cmd_args = ft_tokens_to_args(&data->commands[cmd_index]);
	ft_getpath(data, *cmd_args[0]);
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

/* ************************************************************************** */
/*                                                                            */
/*   Performs cleanup operations after command execution                     */
/*   Closes heredoc synchronization pipes                                    */
/*   Waits for child processes to complete                                   */
/*   Closes any redirected file descriptors                                  */
/* ************************************************************************** */
void	ft_cleanup_execution(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		ft_safe_close(&data->heredoc_sync[i][0]);
		ft_safe_close(&data->heredoc_sync[i][1]);
		i++;
	}
	ft_wait_children(data, data->pids);
	i = 0;
	while (i <= data->cmd_count)
	{
		ft_close_redirect_fds(&data->commands[i].redir);
		i++;
	}
	data->pids = NULL;
	ft_free_tokens(data);
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
	int		i;

	ft_setup_heredoc_sync(data);
	cmd_index = -1;
	data->pids = malloc((data->cmd_count + 1) * sizeof(pid_t));
	if (!data->pids)
		return ;
	i = 0;
	while (i <= data->cmd_count)
	{
		data->pids[i] = -1;
		i++;
	}
	data->prev_pipe = -1;
	while (++cmd_index < data->cmd_count + 1)
	{
		ft_prepare_command(data, cmd_index, &cmd_args);
		if (data->cmd_count == 0 && data->commands[cmd_index]
			.tokens->type == BUILTIN)
			ft_execute_lone_builtin(data, cmd_index, cmd_args);
		else
			ft_handle_command(data, pipefd, cmd_index, cmd_args);
		ft_free_cmd(data, cmd_args);
	}
	ft_cleanup_execution(data);
}
