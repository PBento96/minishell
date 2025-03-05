/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:41:32 by pda-silv          #+#    #+#             */
/*   Updated: 2025/03/05 15:30:26 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_builtin(t_data *data, char **cmd_args)
{
	char	*cmd;
	size_t	len;

	cmd = cmd_args[0];
	len = ft_strlen(cmd) + 1;
	if (!ft_strncmp(OP_EXT, cmd, len))
		return (true);
	(void) data;
	return (false);
}

void	ft_execute_builtin(t_data *data, char **cmd_args)
{
	int		i;
	bool	quit;

	i = 0;
	printf("Executing builtin command: %s\n", cmd_args[0]);
	while (cmd_args[i] != NULL)
	{
		printf("arg[%d]: %s\n", i, cmd_args[i]);
		i++;
	}
	quit = ft_builtin(data, cmd_args);
	perror("ft_builtin");
	ft_free((void **)&data->cmd_path);
	ft_free_array((void **)cmd_args);
	if (quit)
		kill(getppid(), SIGTERM);
	exit(EXIT_FAILURE);
}
