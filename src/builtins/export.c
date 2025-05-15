/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/05/15 21:08:07 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_env_variable(t_data *data, char *var, int count)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return ;
	i = 0;
	while (i < count)
	{
		new_env[i] = data->env[i];
		i++;
	}
	new_env[count] = ft_strdup(var);
	new_env[count + 1] = NULL;
	free(data->env);
	data->env = new_env;
}

static int	update_existing_var(t_data *data, char *var, char *equal_sign)
{
	int		j;
	int		var_len;
	int		found;

	j = 0;
	found = 0;
	var_len = equal_sign - var;
	while (data->env[j])
	{
		if (ft_strncmp(data->env[j], var, var_len) == 0
			&& data->env[j][var_len] == '=')
		{
			free(data->env[j]);
			data->env[j] = ft_strdup(var);
			found = 1;
			break ;
		}
		j++;
	}
	return (found);
}

static void	process_var_with_equal(t_data *data, char *var)
{
	char	*equal_sign;
	int		j;
	int		found;

	equal_sign = ft_strchr(var, '=');
	*equal_sign = '\0';
	found = update_existing_var(data, var, equal_sign);
	*equal_sign = '=';
	if (!found)
	{
		j = 0;
		while (data->env[j])
			j++;
		add_env_variable(data, var, j);
	}
}

static void	process_var_no_equal(t_data *data, char *var)
{
	int		count;
	char	*temp;

	if (var_exists(data->env, var))
		return ;
	count = 0;
	temp = var;
	while (*temp)
	{
		if ((!ft_isalnum(*temp) || !ft_isalpha(*temp)) && *temp != '_')
		{
			write(2, "minishell: export: `", 20);
			write(2, var, ft_strlen(var));
			write(2, "': not a valid identifier\n", 26);
			return ;
		}
		temp++;
	}
	while (data->env[count])
		count++;
	add_env_variable(data, var, count);
}

/************************/
/*Export Builtin Command*/
/************************/
void	ft_export(t_data *data, char **cmd_args)
{
	int		i;
	char	*equal_sign;

	if (!cmd_args[1])
	{
		ft_print_sorted_env(data->env);
		return ;
	}
	i = 1;
	while (cmd_args[i])
	{
		equal_sign = ft_strchr(cmd_args[i], '=');
		if (equal_sign)
			process_var_with_equal(data, cmd_args[i]);
		else
			process_var_no_equal(data, cmd_args[i]);
		i++;
	}
}
