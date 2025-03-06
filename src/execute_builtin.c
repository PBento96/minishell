/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:41:32 by pda-silv          #+#    #+#             */
/*   Updated: 2025/03/06 19:44:57 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_builtin(t_data *data, char **cmd_args)
{
	char	*cmd;
	size_t	len;

	cmd = cmd_args[0];
	len = ft_strlen(cmd) + 1;
	if (!ft_strncmp(OP_EXT, cmd, len))
		kill(getppid(), SIGTERM);
	if (!ft_strncmp(OP_PWD, cmd, len))
		return ;
	if (!ft_strncmp(OP_ECHO, cmd, len))
		return ;
	if (!ft_strncmp(OP_ENV, cmd, len))
		return ;
	if (!ft_strncmp(OP_EXP, cmd, len))
		return ;
	if (!ft_strncmp(OP_UNS, cmd, len))
		return ;
	(void) data;
}
