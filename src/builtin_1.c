/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/25 19:52:03 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char **cmd_args)
{
	int		exit_status;
	int		i;
	int		neg;

	write(1, "exit\n", 5);
	if (!cmd_args[1])
		exit(data->status);

	// Check if argument is numeric
	i = 0;
	neg = 0;
	if (cmd_args[1][i] == '-' || cmd_args[1][i] == '+')
	{
		if (cmd_args[1][i] == '-')
			neg = 1;
		i++;
	}
	exit_status = 0;
	while (cmd_args[1][i])
	{
		if (cmd_args[1][i] < '0' || cmd_args[1][i] > '9')
		{
			write(2, "minishell: exit: ", 17);
			write(2, cmd_args[1], ft_strlen(cmd_args[1]));
			write(2, ": numeric argument required\n", 28);
			exit(2);
		}
		exit_status = exit_status * 10 + (cmd_args[1][i] - '0');
		i++;
	}

	if (cmd_args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		data->status = 1;
		return;
	}

	if (neg)
		exit_status = -exit_status;
	ft_shutdown(data, (unsigned char)exit_status);
}

// Helper function to print environment variables in sorted order
static void	ft_print_sorted_env(char **env)
{
	int		i;
	int		j;
	int		count;
	char	*temp;
	char	**sorted_env;

	// Count environment variables
	count = 0;
	while (env[count])
		count++;

	// Create a copy of the environment
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return;

	for (i = 0; i < count; i++)
		sorted_env[i] = ft_strdup(env[i]);
	sorted_env[count] = NULL;

	// Sort the environment (bubble sort)
	for (i = 0; i < count - 1; i++)
	{
		for (j = 0; j < count - i - 1; j++)
		{
			if (ft_strncmp(sorted_env[j], sorted_env[j + 1], ft_strlen(sorted_env[j])) > 0)
			{
				temp = sorted_env[j];
				sorted_env[j] = sorted_env[j + 1];
				sorted_env[j + 1] = temp;
			}
		}
	}

	// Print the sorted environment with "declare -x" prefix
	for (i = 0; i < count; i++)
	{
		char *equal_sign = ft_strchr(sorted_env[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			ft_printf("declare -x %s=\"%s\"\n", sorted_env[i], equal_sign + 1);
		}
		else
		{
			ft_printf("declare -x %s\n", sorted_env[i]);
		}
	}

	// Free the sorted environment
	for (i = 0; i < count; i++)
		free(sorted_env[i]);
	free(sorted_env);
}

void	ft_export(t_data *data, char **cmd_args)
{
	int		i;
	int		k;
	int		j;
	int		found;
	int		var_len;
	char	*equal_sign;
	char	**new_env;

	if (!cmd_args[1])
	{
		// If no arguments, print all environment variables in sorted order
		ft_print_sorted_env(data->env);
		return;
	}
	i = 1;
	var_len = 0;
	while (cmd_args[i])
	{
		equal_sign = ft_strchr(cmd_args[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0'; // Temporarily split the string at '='
			found = 0;
			j = 0;
			while (data->env[j])
			{
				if (ft_strncmp(data->env[j], cmd_args[i], ft_strlen(cmd_args[i])) == 0
					&& data->env[j][ft_strlen(cmd_args[i])] == '=')
				{
					// Variable already exists, update it
					free(data->env[j]);
					*equal_sign = '='; // Restore the '=' character
					data->env[j] = ft_strdup(cmd_args[i]);
					found = 1;
					break;
				}
				j++;
			}

			if (!found)
			{
				// Variable doesn't exist, add it
				*equal_sign = '='; // Restore the '=' character
				new_env = malloc(sizeof(char *) * (j + 2));
				if (!new_env)
					return;

				for (int k = 0; k < j; k++)
					new_env[k] = data->env[k];

				new_env[j] = ft_strdup(cmd_args[i]);
				new_env[j + 1] = NULL;

				free(data->env);
				data->env = new_env;
			}
		}
		else
		{
			// No '=' in the argument, just declare without setting a value
			// Check if the variable is already in the environment
			found = 0;
			j = 0;
			while (data->env[j])
			{
				var_len = ft_strlen(cmd_args[i]);
				if (ft_strncmp(data->env[j], cmd_args[i], var_len) == 0 &&
					(data->env[j][var_len] == '=' || data->env[j][var_len] == '\0'))
				{
					found = 1;
					break;
				}
				j++;
			}
			// If not found, add it to the environment
			if (!found)
			{
				// Count environment variables
				k = 0;
				while (data->env[k])
					k++;

				// Create new environment with the variable
				new_env = malloc(sizeof(char *) * (k + 2));
				if (!new_env)
					return;

				for (int m = 0; m < k; m++)
					new_env[m] = data->env[m];

				new_env[k] = ft_strdup(cmd_args[i]);
				new_env[k + 1] = NULL;

				free(data->env);
				data->env = new_env;
			}
		}
		i++;
	}
}

void	ft_unset(t_data *data, char **cmd_args)
{
	int	i;
	int	j;
	int	k;
	int	var_len;
	char	**new_env;

	if (!cmd_args[1])
		return;

	i = 1;
	while (cmd_args[i])
	{
		j = 0;
		while (data->env[j])
		{
			var_len = 0;
			while (cmd_args[i][var_len] && cmd_args[i][var_len] != '=')
				var_len++;

			if (ft_strncmp(data->env[j], cmd_args[i], var_len) == 0 &&
				(data->env[j][var_len] == '=' || data->env[j][var_len] == '\0'))
			{
				// Count environment variables
				k = 0;
				while (data->env[k])
					k++;

				// Create new environment without the variable
				new_env = malloc(sizeof(char *) * k);
				if (!new_env)
					return;

				// Copy all variables except the one to be removed
				k = 0;
				for (int m = 0; data->env[m]; m++)
				{
					if (m != j)
						new_env[k++] = ft_strdup(data->env[m]);
				}
				new_env[k] = NULL;

				// Free the old environment
				for (int m = 0; data->env[m]; m++)
					free(data->env[m]);
				free(data->env);

				// Set the new environment
				data->env = new_env;
				break;
			}
			j++;
		}
		i++;
	}
}

void	ft_set_data_env(t_data *data, char *OLDPWD)
{
	int i;
	char *new_env;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
		{
			new_env = ft_strjoin("OLDPWD=", OLDPWD);
			if (new_env)
			{
				free(data->env[i]);
				data->env[i] = new_env;
			}
		}
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			new_env = ft_strjoin("PWD=", data->cwd);
			if (new_env)
			{
				free(data->env[i]);
				data->env[i] = new_env;
			}
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
