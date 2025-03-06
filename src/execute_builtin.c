/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:41:32 by pda-silv          #+#    #+#             */
/*   Updated: 2025/03/06 10:29:35 by pda-silv         ###   ########.fr       */
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

bool	ft_execute_builtin(t_data *data, char **cmd_args)
{
	bool	quit;

	quit = ft_builtin(data, cmd_args);
	perror("ft_builtin");
	return (quit);
}
