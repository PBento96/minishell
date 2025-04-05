/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/05 10:33:32 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************/
/*Update ENV*/
/************/
void	ft_set_env(char **env_var, char *change, char *search)
{
	char	*new_env;

	if (ft_strncmp(*env_var, search, ft_strlen(search)) == 0)
	{
		new_env = ft_strjoin(search, change);
		if (new_env)
		{
			free(*env_var);
			*env_var = new_env;
		}
	}
}

/*********************/
/*Seach Env to Update*/
/*********************/
void	ft_set_data_env(t_data *data, char *OLDPWD)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		ft_set_env(&data->env[i], OLDPWD, "OLDPWD=");
		ft_set_env(&data->env[i], data->cwd, "PWD=");
		i++;
	}
}

/********************/
/*CD Builtin Command*/
/********************/
void	ft_cd(t_data *data, char **cmd_args)
{
	char OLDPWD[MAX_CWD_SIZE];
	char *OLDPWD_cp;
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
	OLDPWD_cp = ft_strdup(OLDPWD);
	ft_set_data_env(data, OLDPWD_cp);
}
