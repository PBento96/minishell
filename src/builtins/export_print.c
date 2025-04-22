/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:27:48 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/22 21:45:11 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
