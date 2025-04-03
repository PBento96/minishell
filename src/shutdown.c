/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:37:51 by pda-silv          #+#    #+#             */
/*   Updated: 2025/03/26 17:57:33 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->cmd_count)
	{
		j = 0;
		while (j < data->commands[i].token_count)
		{
			if (data->commands[i].tokens[j].value)
				ft_free((void **)&data->commands[i].tokens[j].value);
			j++;
		}
		i++;
	}
	if (data->cmd_path)
		ft_free((void **)&data->cmd_path);
	if (data->pids)
		ft_free((void **)&data->pids);
}

void	ft_free_env_array(t_data *data)
{
	int	i;

	i = 0;
	if (!data->env)
		return ;
	while (data->env[i])
	{
		ft_free((void **)&data->env[i]);
		i++;
	}
	ft_free((void **)&data->env);
}

void	ft_shutdown(t_data **data, int retval)
{
	ft_printf(C_YELLOW"\nExiting Minishell...\n"RESET_COLOR);

	if (*data)
	{
		// Free command history if using readline
		clear_history();

		// Free any input that might still be allocated
		if ((*data)->input)
			ft_free((void **)&((*data)->input));

		// Free any token lists or parse trees
		ft_free_tokens(*data);

		// Free environment variables if they were duplicated
		ft_free_env_array(*data);

		// Finally free the main data structure
		ft_free((void **)data);
	}

	exit(retval);
}
