/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/07 09:15:56 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_handle_pipes(data, pipefd, cmd_index);
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

void	ft_execute(t_data *data)
{
	int		pipefd[2];
	int		cmd_index;
	char	**cmd_args;

	cmd_index = -1;
	data->pids = malloc((data->cmd_count + 1) * sizeof(pid_t));
	if (!data->pids)
		return ;
	data->prev_pipe = -1;
	while (++cmd_index <= data->cmd_count && !g_signal)
	{
		ft_prepare_command(data, cmd_index, &cmd_args);
		ft_create_child_process(data, pipefd, cmd_index, cmd_args);
		if (data->pids[cmd_index] > 0)
			ft_handle_parent(data, pipefd, cmd_index);
		ft_free_cmd(data, cmd_args);
	}
	ft_wait_children(data, data->pids);
}
