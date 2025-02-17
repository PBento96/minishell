/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/02/17 17:37:02 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_findcmd(char **dirs, char *cmd)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		ft_free((void **)&tmp);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		ft_free((void **)&cmd_path);
		i++;
	}
	return (NULL);
}

char	*ft_getenv(const char *name, char **env)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	ft_getpath(t_data *data, int i)
{
	char	*path;
	char	**dirs;
	char	*path_copy;

	path = ft_getenv("PATH", data->env);
	if (!path)
	{
		data->cmd_path = NULL;
		return ;
	}
	path_copy = ft_strdup(path);
	if (!path_copy)
	{
		data->cmd_path = NULL;
		return ;
	}
	dirs = ft_split(path_copy, ':');
	ft_free((void **)&path_copy);
	if (!dirs)
	{
		data->cmd_path = NULL;
		return ;
	}
	data->cmd_path = ft_findcmd(dirs, data->commands[i].tokens[0].value);
	ft_free((void **)&dirs);
}

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
	execve(data->cmd_path, cmd_args, data->env);
	perror("execve");
	ft_free((void **)&data->cmd_path);
	ft_free_array((void **)cmd_args);
	exit(EXIT_FAILURE);
}

void	ft_execute(t_data *data)
{
	pid_t	pid;
	int		status;
	int		command;
	char	**cmd_args;

	command = 0;
	while(command <= data->cmd_count)
	{
		printf("Command: %d\n", command); // Debug print
		printf("Token Command: %s\n", data->commands[command].tokens[0].value); // Debug print

		cmd_args = ft_tokens_to_args(data->commands[command].tokens, data->commands[command].token_count);
		ft_getpath(data, command);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			ft_free((void **)&data->cmd_path);
			ft_free_array((void **)cmd_args);
			return;
		}
		else if (pid == 0)
			ft_execute_command(data, cmd_args);
		else
		{
			waitpid(pid, &status, 0);
			ft_free((void **)&data->cmd_path);
			ft_free_array((void **)cmd_args);
		}
		command++;
	}
}
