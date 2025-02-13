/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/02/13 23:13:32 by joseferr         ###   ########.fr       */
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

char	*ft_getpath(t_data *data)
{
	char	*cmd_path;
	char	*path;
	char	**dirs;
	char	*path_copy;

	path = ft_getenv("PATH", data->env);
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	if (!path_copy)
		return (NULL);
	dirs = ft_split(path_copy, ':');
	ft_free((void **)&path_copy);
	if (!dirs)
		return (NULL);
	cmd_path = ft_findcmd(dirs, data->commands[0].tokens[0].value);
	ft_free((void **)&dirs);
	return (cmd_path);
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

void	ft_execute_command(char *cmd_path, char **cmd_args, char **env)
{
	execve(cmd_path, cmd_args, env);
	perror("execve");
	ft_free((void **)&cmd_path);
	ft_free_array((void **)cmd_args);
	exit(EXIT_FAILURE);
}

void	ft_fork_and_execute(char *cmd_path, char **cmd_args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_free((void **)&cmd_path);
		ft_free_array((void **)cmd_args);
		return;
	}
	else if (pid == 0)
	{
		// Child process
		ft_execute_command(cmd_path, cmd_args, env);
	}
	else
	{
		// Parent process
		waitpid(pid, &status, 0);
		ft_free((void **)&cmd_path);
		ft_free_array((void **)cmd_args);
	}
}

void	ft_execute(t_data *data)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = ft_getpath(data);
	if (!cmd_path)
	{
		ft_printf("Command not found: %s\n", data->commands[0].tokens[0].value);
		return;
	}
	cmd_args = ft_tokens_to_args(data->commands[0].tokens, data->commands[0].token_count);
	if (!cmd_args)
	{
		perror("malloc");
		ft_free((void **)&cmd_path);
		return;
	}
	ft_fork_and_execute(cmd_path, cmd_args, data->env);
}
