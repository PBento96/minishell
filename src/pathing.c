/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:24:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/05/31 14:03:17 by joseferr         ###   ########.fr       */
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

void	ft_getpath(t_data *data, char *cmd)
{
	char	**path_dirs;
	char	*path_env;

	if (!cmd || cmd[0] == '\0')
	{
		data->cmd_path = NULL;
		return;
	}
	if (ft_is_builtin(cmd))
	{
		data->cmd_path = NULL;
		return;
	}
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			data->cmd_path = ft_strdup(cmd);
		else
			data->cmd_path = NULL;
		return;
	}
	path_env = ft_getenv("PATH", data->env);
	if (!path_env)
	{
		data->cmd_path = NULL;
		return;
	}
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
	{
		data->cmd_path = NULL;
		return;
	}
	data->cmd_path = ft_findcmd(path_dirs, cmd);
	ft_free_array((void **)path_dirs);
}
