/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/05/29 22:24:33 by pda-silv         ###   ########.fr       */
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

static int	update_existing_var(t_data *data, char *var_name, char *end_ptr,
				char *full_var)
{
	int		j;
	int		var_len;
	int		found;

	j = 0;
	found = 0;
	var_len = end_ptr - var_name;
	while (data->env[j])
	{
		if (ft_strncmp(data->env[j], var_name, var_len) == 0
			&& (data->env[j][var_len] == '=' || data->env[j][var_len] == '\0'))
		{
			free(data->env[j]);
			data->env[j] = ft_strdup(full_var);
			found = 1;
			break ;
		}
		j++;
	}
	return (found);
}

static void	process_var_with_equal(t_data *data, char *var)
{
	char	*var_copy;
	int		j;
	int		found;

	var_copy = ft_strdup(var);
	if (!var_copy)
		return ;
	*ft_strchr(var_copy, '=') = '\0';
	found = update_existing_var(data, var_copy, ft_strchr(var_copy, '\0'), var);
	free(var_copy);
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
	if (ft_isdigit(*temp))
	{
		write_error_message(var);
		return ;
	}
	temp++;
	while (*temp)
	{
		if ((!ft_isalnum(*temp)) && *temp != '_')
		{
			write_error_message(var);
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
