/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/24 10:22:14 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_handle_redirections(t_data *data, int cmd_index)
{
    t_token *tokens;
    int fd_in = -1;
    int fd_out = -1;
    int i = 0;

    tokens = data->commands[cmd_index].tokens;

    while (i < data->commands[cmd_index].token_count)
    {
        if (tokens[i].type == REDIR_IN) // <
        {
            if (i + 1 < data->commands[cmd_index].token_count)
            {
                if (fd_in != -1)
                    close(fd_in);
                fd_in = open(tokens[i + 1].value, O_RDONLY);
                if (fd_in == -1)
                {
                    perror(tokens[i + 1].value);
                    return (0);
                }
                // Make sure to close the old STDIN_FILENO first
                if (dup2(fd_in, STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    close(fd_in);
                    return (0);
                }
                i++; // Skip the filename token
            }
        }
        else if (tokens[i].type == REDIR_OUT) // >
        {
            if (i + 1 < data->commands[cmd_index].token_count)
            {
                if (fd_out != -1)
                    close(fd_out);
                fd_out = open(tokens[i + 1].value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_out == -1)
                {
                    perror(tokens[i + 1].value);
                    return (0);
                }
                if (dup2(fd_out, STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    close(fd_out);
                    return (0);
                }
                i++; // Skip the filename token
            }
        }
        else if (tokens[i].type == REDIR_APPEND) // >>
        {
            if (i + 1 < data->commands[cmd_index].token_count)
            {
                if (fd_out != -1)
                    close(fd_out);
                fd_out = open(tokens[i + 1].value, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd_out == -1)
                {
                    perror(tokens[i + 1].value);
                    return (0);
                }
                if (dup2(fd_out, STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    close(fd_out);
                    return (0);
                }
                i++; // Skip the filename token
            }
        }
        i++;
    }

    // Close the original file descriptors after duplication
    if (fd_in != -1)
        close(fd_in);
    if (fd_out != -1)
        close(fd_out);
    return (1);
}

void	ft_execute_command(t_data *data, char **cmd_args, t_token_type type)
{
	int		i;

	i = 0;
	while (cmd_args[i] != NULL)
	{
		printf("arg[%d]: %s\n", i, cmd_args[i]);
		i++;
	}
	if (type == BUILTIN)
		ft_execute_builtin(data, cmd_args);
	else
	{
		printf("Executing command: %s\n", data->cmd_path);
		execve(data->cmd_path, cmd_args, data->env);
		perror("execve");
	}
	ft_free((void **)&data->cmd_path);
	ft_free_array((void **)cmd_args);
	exit(EXIT_FAILURE);
}

static void	ft_prepare_command(t_data *data, int cmd_index, char ***cmd_args)
{
	*cmd_args = ft_tokens_to_args(data->commands[cmd_index].tokens,
			data->commands[cmd_index].token_count);
	ft_getpath(data, cmd_index);
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
        ft_handle_pipes(data, pipefd, cmd_index);
        // Handle redirections before executing
        if (!ft_handle_redirections(data, cmd_index))
            exit(EXIT_FAILURE);
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

void ft_execute(t_data *data)
{
    int     pipefd[2];
    int     cmd_index;
    char    **cmd_args;

    cmd_index = -1;
    data->piped = 0;
    // Fix: Allocate the correct size for pids
    data->pids = malloc((data->cmd_count + 1) * sizeof(pid_t));
    if (!data->pids)
        return;
    // Initialize all elements to avoid uninitialized memory errors
    for (int i = 0; i <= data->cmd_count; i++)
        data->pids[i] = -1;

    data->prev_pipe = -1;
    while (++cmd_index <= data->cmd_count && !g_signal)
    {
        // Only set piped to 1 if there are actual pipe commands
        data->piped = (data->cmd_count > 0) ? 1 : 0;
        ft_prepare_command(data, cmd_index, &cmd_args);
        if (data->cmd_count == 0 &&
            data->commands[cmd_index].tokens->type == BUILTIN)
        {
            // Save original stdin/stdout
            int stdin_copy = dup(STDIN_FILENO);
            int stdout_copy = dup(STDOUT_FILENO);

            // Handle redirections
            if (ft_handle_redirections(data, cmd_index))
                ft_execute_builtin(data, cmd_args);

            // Restore original stdin/stdout
            dup2(stdin_copy, STDIN_FILENO);
            dup2(stdout_copy, STDOUT_FILENO);
            close(stdin_copy);
            close(stdout_copy);
        }
        else
        {
            ft_create_child_process(data, pipefd, cmd_index, cmd_args);
            if (data->pids[cmd_index] > 0)
                ft_handle_parent(data, pipefd, cmd_index);
        }
        ft_free_cmd(data, cmd_args);
    }
    if (data->piped == 1)
        ft_wait_children(data, data->pids);
}
