/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/03/26 18:05:26 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_arg(char *arg, int *exit_value)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			neg = 1;
		i++;
	}
	*exit_value = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		*exit_value = *exit_value * 10 + (arg[i] - '0');
		i++;
	}
	if (neg)
		*exit_value = -*exit_value;
	return (1);
}

static void	handle_exit_error(char *arg)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
	exit(2);
}

void	ft_exit(t_data *data, char **cmd_args)
{
	int	exit_status;

	write(1, "exit\n", 5);
	exit_status = 0;
	if (!cmd_args[1])
		ft_shutdown(&data, (unsigned char)exit_status);
	if (!is_numeric_arg(cmd_args[1], &exit_status))
		handle_exit_error(cmd_args[1]);
	if (cmd_args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		data->status = 1;
		return ;
	}
	if (data->piped == 0)
		ft_shutdown(&data, (unsigned char)exit_status);
}

static void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static char	**dup_env_array(char **env)
{
	int		count;
	char	**dup;
	int		i;

	count = 0;
	while (env[count])
		count++;
	dup = malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(env[i]);
		if (!dup[i])
		{
			while (--i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[count] = NULL;
	return (dup);
}

static void	sort_env_array(char **env)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	while (env[size])
		size++;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(env[j], env[j + 1], size) > 0)
				swap_strings(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

static void	print_env_with_declare(char **env)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (env[i])
	{
		write(1, "declare -x ", 11);
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			write(1, env[i], equal_sign - env[i] + 1);
			write(1, "\"", 1);
			write(1, equal_sign + 1, ft_strlen(equal_sign + 1));
			write(1, "\"", 1);
		}
		else
			write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}

static void	free_env_array(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	ft_print_sorted_env(char **env)
{
	char	**sorted_env;

	sorted_env = dup_env_array(env);
	if (!sorted_env)
		return ;
	sort_env_array(sorted_env);
	print_env_with_declare(sorted_env);
	free_env_array(sorted_env);
}

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

static int	var_exists(char **env, char *var)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0 &&
			(env[i][var_len] == '=' || env[i][var_len] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

static void	process_var_no_equal(t_data *data, char *var)
{
	int		count;

	if (var_exists(data->env, var))
		return ;
	count = 0;
	while (data->env[count])
		count++;
	add_env_variable(data, var, count);
}

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
