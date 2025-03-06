/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/06 19:04:22 by pda-silv         ###   ########.fr       */
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

void	ft_handle_parent_process(pid_t pid, int pipefd[2], int command)
{
	int	status;

	waitpid(pid, &status, 0);
	close(pipefd[1]);
	if (command != 0)
		close(pipefd[0]);
}

void	ft_execute(t_data *data)
{
	int		pipefd[2];
	pid_t	pid;
	int		c;
	char	**cmd_args;
	pid_t	*pids;

	c = -1;
	while (++c <= data->cmd_count && !g_signal)
	{
		cmd_args = ft_tokens_to_args(data->commands[c].tokens, \
			data->commands[c].token_count);
		ft_getpath(data, c);
		ft_setup_pipes(pipefd);
		pid = fork();
		if (pid == -1)
			ft_pipe_error(data, cmd_args);
		else if (pid == 0)
		{
			ft_handle_pipes(data, pipefd, c);
			ft_execute_command(data, cmd_args, data->commands[c].tokens->type);
		}
		else
			ft_handle_parent_process(pid, pipefd, c);
		ft_free_cmd(data, cmd_args);
	}
	ft_wait_children(data, pids);
}
