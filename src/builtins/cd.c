/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/05/31 14:14:21 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************/
/*Update ENV*/
/************/
void	ft_set_env(char **envvar, char *change, char *search)
{
	char	*newenv;

	if (ft_strncmp(*envvar, search, ft_strlen(search)) == 0)
	{
		newenv = ft_strjoin(search, change);
		if (newenv)
		{
			free(*envvar);
			*envvar = newenv;
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
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
			ft_set_env(&data->env[i], data->cwd, "PWD=");
		else if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
			ft_set_env(&data->env[i], OLDPWD, "OLDPWD=");
		i++;
	}
	free(OLDPWD);
}

/********************/
/*CD Builtin Command*/
/********************/
void	ft_cd(t_data *data, char **cmdargs)
{
	char	oldpwd[MAX_CWD_SIZE];
	char	*copy;
	char	*path;

	if (!cmdargs[1])
	{
		path = ft_getenv("HOME", data->env);
		if (!path)
		{
			write(2, "cd: Home not set\n", 18);
			return ;
		}
	}
	else
		path = cmdargs[1];
	getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
	getcwd(data->cwd, sizeof(data->cwd));
	copy = ft_strdup(oldpwd);
	ft_set_data_env(data, copy);
	data->status = 0;
}
