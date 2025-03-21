/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/21 22:12:06 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char **cmd_args)
{
	(void)data;
	(void)cmd_args;
	kill(getppid(), SIGTERM);
}

void	ft_export(t_data *data, char **cmd_args)
{
	(void)data;
	(void)cmd_args;
}

void	ft_unset(t_data *data, char **cmd_args)
{
	(void)data;
	(void)cmd_args;
}
void	ft_set_data_env(t_data *data, char *OLDPWD)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "OLDPWD=", 6) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strjoin("OLDPWD=", OLDPWD);
		}
		if (ft_strncmp(data->env[i], "PWD=", 3) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strjoin("PWD=", data->cwd);
		}
		i++;
	}
}
void	ft_cd(t_data *data, char **cmd_args)
{
	char OLDPWD[MAX_CWD_SIZE];
	char *path;

	if (!cmd_args[1])
	{
		path = ft_getenv("HOME", data->env);
		if (!path)
		{
			write(2, "cd: Home not set\n", 18);
			return;
		}
	}
	else
		path = cmd_args[1];
	getcwd(OLDPWD, sizeof(OLDPWD));
	if (chdir(path) != 0)
	{
		perror("cd");
		return;
	}
	getcwd(data->cwd, sizeof(data->cwd));
	ft_set_data_env(data, OLDPWD);
}
