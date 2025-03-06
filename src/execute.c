/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/06 10:31:23 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tokens_to_args(t_token *tokens, int token_count)
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

void	ft_execute_command(t_data *data, char **cmd_args, t_token_type type)
{
	int		i;
	bool	quit;

	i = 0;
	printf("Executing command: %s\n", data->cmd_path);
	while (cmd_args[i] != NULL)
	{
		printf("arg[%d]: %s\n", i, cmd_args[i]);
		i++;
	}
	if (type == BUILTIN)
		quit = ft_execute_builtin(data, cmd_args);
	else
		execve(data->cmd_path, cmd_args, data->env);
	perror("execve");
	ft_free((void **)&data->cmd_path);
	ft_free_array((void **)cmd_args);
	if (quit)
		kill(getppid(), SIGTERM);
	exit(EXIT_FAILURE);
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
	int		c;
	char	**cmd_args;

	c = 0;
	while (c <= data->cmd_count)
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
		c++;
	}
}
