/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/02/18 14:10:06 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_tokens_to_args(t_token *tokens, int token_count)
{
	char	**args;
	int		i;

	args = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		args[i] = ft_strdup(tokens[i].value);
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	ft_execute_command(t_data *data, char **cmd_args)
{
	int i;

	i = 0;
	printf("Executing command: %s\n", data->cmd_path);
	while ( cmd_args[i] != NULL)
	{
		printf("arg[%d]: %s\n", i, cmd_args[i]);
		i++;
	}
	execve(data->cmd_path, cmd_args, data->env);
	perror("execve");
	ft_free((void **)&data->cmd_path);
	ft_free_array((void **)cmd_args);
	exit(EXIT_FAILURE);
}

void	ft_setup_pipes(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	ft_handle_pipes(t_data *data, int pipefd[2], int command)
{
	if (command != 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	if (command != data->cmd_count)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	close(pipefd[0]);
	close(pipefd[1]);
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
	int		command;
	char	**cmd_args;

	command = 0;
	while (command <= data->cmd_count)
	{
		cmd_args = ft_tokens_to_args(data->commands[command].tokens, data->commands[command].token_count);
		ft_getpath(data, command);
		ft_setup_pipes(pipefd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			ft_free((void **)&data->cmd_path);
			ft_free_array((void **)cmd_args);
			return;
		}
		else if (pid == 0)
		{
			ft_handle_pipes(data, pipefd, command);
			ft_execute_command(data, cmd_args);
		}
		else
		{
			ft_handle_parent_process(pid, pipefd, command);
			ft_free((void **)&data->cmd_path);
			ft_free_array((void **)cmd_args);
		}
		command++;
	}
}
