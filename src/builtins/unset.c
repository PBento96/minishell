/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/05 10:33:23 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_data *data, int j)
{
	int		k;
	int		m;
	char	**new_env;

	k = 0;
	while (data->env[k])
		k++;
	new_env = malloc(sizeof(char *) * k);
	if (!new_env)
		return ;
	k = 0;
	m = 0;
	while (data->env[m])
	{
		if (m != j)
			new_env[k++] = ft_strdup(data->env[m]);
		m++;
	}
	new_env[k] = NULL;
	m = 0;
	while (data->env[m])
		free(data->env[m++]);
	free(data->env);
	data->env = new_env;
}

static int	is_matching_var(char *env_var, char *arg)
{
	int	var_len;

	var_len = 0;
	while (arg[var_len] && arg[var_len] != '=')
		var_len++;
	if (ft_strncmp(env_var, arg, var_len) == 0 &&
		(env_var[var_len] == '=' || env_var[var_len] == '\0'))
		return (1);
	return (0);
}
/*********************/
/*Seach Env to Update*/
/*********************/
void	ft_unset(t_data *data, char **cmd_args)
{
	int	i;
	int	j;

	if (!cmd_args[1])
		return ;
	i = 1;
	while (cmd_args[i])
	{
		j = 0;
		while (data->env[j])
		{
			if (is_matching_var(data->env[j], cmd_args[i]))
			{
				remove_env_var(data, j);
				break ;
			}
			j++;
		}
		i++;
	}
}
