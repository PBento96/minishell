/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:24:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/21 21:20:28 by joseferr         ###   ########.fr       */
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

	path = ft_getenv("PATH", data->env);
	if (!path)
	{
		data->cmd_path = NULL;
		return ;
	}
	dirs = ft_split(path, ':');
	ft_free((void **)&path);
	if (!dirs)
	{
		data->cmd_path = NULL;
		return ;
	}
	data->cmd_path = ft_findcmd(dirs, data->commands[i].tokens[0].value);
	ft_free((void **)&dirs);
}
